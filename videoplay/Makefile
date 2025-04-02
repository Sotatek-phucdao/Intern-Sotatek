# Biến cấu hình
CXX = g++  # Trình biên dịch
CXXFLAGS = -std=c++11 -g  # Cờ biên dịch, bao gồm các cờ coverage
LDFLAGS = -pthread  # Các thư viện cần link
SRC = main.cpp  # Các file nguồn
OBJ = main.o  # Các file object (từ file nguồn)
TARGET = main  # Tên chương trình cuối cùng

# Quy tắc mặc định: Biên dịch chương trình cuối cùng
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Quy tắc biên dịch các file nguồn thành file object
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Quy tắc để dọn dẹp các file object và chương trình cuối
clean:
	rm -f $(OBJ) $(TARGET) *.gcda *.gcno *.gcov

# Quy tắc để chạy chương trình kiểm tra (test)
run: $(TARGET)
	./$(TARGET)

