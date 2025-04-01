#include <gtest/gtest.h>
#include "ringbuffer.hpp"
using namespace std;

// Test case
TEST(AdditionTest, HandlesPositiveNumbers) {
    ringbuffer_init(5);
    
    EXPECT_EQ(ringbuffer_add(10),0);
    EXPECT_EQ(ringbuffer_add(20),0);
    EXPECT_EQ(ringbuffer_add(30),0);
    EXPECT_EQ(ringbuffer_size(),3);
    EXPECT_EQ(ringbuffer_is_empty(),0);
    EXPECT_EQ(ringbuffer_is_full(),0);
    EXPECT_EQ(ringbuffer_remove(10),0);
}

// Hàm main chạy test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
