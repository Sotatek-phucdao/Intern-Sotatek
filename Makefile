# Biến cấu hình
CXX = g++  # Trình biên dịch
CXXFLAGS = -fprofile-arcs -ftest-coverage -std=c++11 -g  # Cờ biên dịch, bao gồm các cờ coverage
LDFLAGS = -lgtest -lgtest_main -pthread -lgcov  # Các thư viện cần link
SRC = test.cpp  # Các file nguồn
OBJ = test.o  # Các file object (từ file nguồn)
TARGET = test  # Tên chương trình cuối cùng

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

# Quy tắc để tạo báo cáo coverage (bằng lệnh gcov)
coverage: $(TARGET)
	./$(TARGET)
	gcov test.cpp
