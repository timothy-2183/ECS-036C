#include "deque.h"
#include <gtest/gtest.h>

// Test Case: Verify that a new deque is empty
TEST(DequeTest, EmptyInitially) {
    Deque<int> dq;
    EXPECT_TRUE(dq.Empty());
    EXPECT_EQ(dq.Size(), 0);
}

// Test Case: All push and pop and check size and elements
TEST(DequeTest, PushandPop) {
    Deque<int> dq;
    dq.PushBack(10);
    dq.PushBack(20);
    dq.PushBack(30);
    EXPECT_EQ(dq.Size(), 3);
    EXPECT_EQ(dq.Front(), 10);
    EXPECT_EQ(dq.Back(), 30);
    dq.PushFront(10);
    dq.PushFront(20);
    dq.PushFront(30);
    EXPECT_EQ(dq.Size(), 6);
    EXPECT_EQ(dq.Front(), 30);
    EXPECT_EQ(dq.Back(), 30);
    dq.PushBack(1);
    dq.PushBack(2);
    dq.PushBack(3);
    dq.PopFront();
    EXPECT_EQ(dq.Size(), 8);
    EXPECT_EQ(dq.Front(), 20);
    dq.PushBack(1);
    dq.PushBack(2);
    dq.PushBack(3);
    dq.PopBack();
    EXPECT_EQ(dq.Size(), 10);
    EXPECT_EQ(dq.Back(), 2);
}

// Test Case: Check circular array feature of deque
TEST(DequeTest, CircularBehavior) {
    Deque<int> dq;
    for (int i = 0; i < 10; i++) {
        dq.PushBack(i);
    }
    for (int i = 0; i < 5; i++) {
        dq.PopFront();
    }
    for (int i = 10; i < 15; i++) {
        dq.PushBack(i);
    }
    EXPECT_EQ(dq.Front(), 5);
    EXPECT_EQ(dq.Back(), 14);
    EXPECT_EQ(dq.Size(), 10);
}
// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
