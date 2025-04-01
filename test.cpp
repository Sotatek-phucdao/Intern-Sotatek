#include <gtest/gtest.h>
#include <thread>
#include <atomic>
#include "ringbuffer.hpp"
using namespace std;

// Hàm kiểm thử với đa luồng
void add_to_ringbuffer(int value, atomic<int>& counter) {
    EXPECT_EQ(ringbuffer_add(value), 0);  // Thêm giá trị vào vòng đệm
    counter++;
}

TEST(AdditionTest, HandlesPositiveNumbers){
    ringbuffer_init(5);
    EXPECT_EQ(ringbuffer_add(10),0);
    EXPECT_EQ(ringbuffer_add(20),0);
    EXPECT_EQ(ringbuffer_add(30),0);
    EXPECT_EQ(ringbuffer_size(),3);
    EXPECT_EQ(ringbuffer_is_empty(),0);
    EXPECT_EQ(ringbuffer_is_full(),0);
    EXPECT_EQ(ringbuffer_remove(10),0);
    EXPECT_EQ(ringbuffer_remove(20),0);
    EXPECT_EQ(ringbuffer_remove(30),0);
    EXPECT_EQ(ringbuffer_remove(10),-1);
    EXPECT_EQ(ringbuffer_size(),0);
    EXPECT_EQ(ringbuffer_is_empty(),1);
    EXPECT_EQ(ringbuffer_is_full(),0);
}
TEST(MultithreadedRingBufferTest, HandlesMultithreadedAdditions) {
    ringbuffer_init(5);
    atomic<int> counter(0);

    // Tạo nhiều luồng để thêm phần tử vào vòng đệm
    thread t1(add_to_ringbuffer, 10, ref(counter));
    thread t2(add_to_ringbuffer, 20, ref(counter));
    thread t3(add_to_ringbuffer, 30, ref(counter));
    
    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(counter.load(), 3);  // Đảm bảo rằng 3 phần tử đã được thêm vào
    EXPECT_EQ(ringbuffer_size(), 3);  // Kiểm tra kích thước của vòng đệm
    EXPECT_EQ(ringbuffer_is_empty(), 0);  // Kiểm tra vòng đệm không rỗng
    EXPECT_EQ(ringbuffer_is_full(), 0);  // Kiểm tra vòng đệm không đầy
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
