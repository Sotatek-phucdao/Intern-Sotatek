#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cstdlib> // For system()
#include <algorithm>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
pid_t launch_ffplay(const std::string& video_path) {
    pid_t pid = fork();

    if (pid == -1) {
        // Fork lỗi
        perror("fork failed");
        return -1;
    } else if (pid == 0) {
        // --- Tiến trình con ---
        std::vector<char*> args;
        args.push_back(strdup("ffplay")); // Tên chương trình
        args.push_back(strdup(video_path.c_str())); // Đường dẫn video
        // Thêm các tùy chọn khác nếu cần
        args.push_back(nullptr); // Kết thúc bằng NULL

        execvp(args[0], args.data());

        
        perror("execvp failed");
        for(char* arg : args) { free(arg); }
        exit(EXIT_FAILURE); // Thoát tiến trình con với lỗi

    } else {
        // --- Tiến trình cha ---
        std::cout << "Child process (ffplay) started with PID: " << pid << std::endl;
        return pid; // Trả về PID của con
    }
}
int video_time(const std::string& video_path) {
    // Lệnh ffprobe để lấy thông tin về video
    std::string command = "ffprobe -v quiet -print_format json -show_format \"" + video_path + "\"";
    
    FILE* pipe = popen(command.c_str(), "r");
    
    // Kiểm tra xem pipe có mở thành công không
    if (pipe == nullptr) {
        std::cerr << "Error: Unable to open pipe." << std::endl;
        return 0;
    }

    // Đọc kết quả từ pipe
    char buffer[128];
    std::string output = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output += buffer;
    }

    // Đóng pipe
    fclose(pipe);

    // Tìm thông tin "duration" trong chuỗi JSON trả về từ ffprobe
    std::string duration_str;
    size_t pos = output.find("\"duration\":");
    if (pos != std::string::npos) {
        pos += 11; // "duration": có độ dài 11 ký tự
        size_t end_pos = output.find(",", pos);  // Tìm dấu phẩy sau duration
        if (end_pos == std::string::npos) {
            end_pos = output.find("}", pos);  // Tìm dấu ngoặc đóng nếu không có dấu phẩy
        }
        duration_str = output.substr(pos, end_pos - pos);  // Cắt lấy giá trị duration
    }

    if (!duration_str.empty()) {
        std::cout << "Duration: " << duration_str << " seconds" << std::endl;
        int time = 0,i;
        while (i < duration_str.size())
        {
            if (duration_str[i] == '.')
            {
                break;
            }
            if (duration_str[i] >= 48 && duration_str[i] <= 57)
            {
              time = time*10+ (duration_str[i]-48);
            }
            i++;
        }
        return time+1;
        
    } else {
        std::cout << "Duration not found!" << std::endl;
        return 0;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_path> " << std::endl;
        return 1;
    }

    std::string video_path = argv[1];
   
    
    pid_t ffplay_pid = launch_ffplay(video_path);

    if (ffplay_pid > 0) {
        waitpid(ffplay_pid, nullptr, 0);
    }

    return 0;
}
