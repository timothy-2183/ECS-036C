#include <gtest/gtest.h>
#include "./stack_vector.h"
/*
 * Testing
 */
TEST(StackVector, Stack)
{
    Stack<int> s;
    ASSERT_EQ(s.Size(), 0);
    /* Test some exceptions */
    ASSERT_THROW(s.Top(), std::underflow_error);
    ASSERT_THROW(s.Pop(), std::underflow_error);
    /* Insert item */
    s.Push(23);
    ASSERT_EQ(s.Size(), 1);
    ASSERT_EQ(s.Top(), 23);
    /* Insert item at the back */
    s.Push(42);
    ASSERT_EQ(s.Size(), 2);
    ASSERT_EQ(s.Top(), 42);
    /* Insert item at the front */
    s.Push(99);
    ASSERT_EQ(s.Size(), 3);
    ASSERT_EQ(s.Top(), 99);
    /* Pop */
    s.Pop();
    ASSERT_EQ(s.Size(), 2);
    ASSERT_EQ(s.Top(), 42);
    /* Pop */
    s.Pop();
    ASSERT_EQ(s.Size(), 1);
    ASSERT_EQ(s.Top(), 23);
    /* Delete again */
    s.Pop();
    ASSERT_EQ(s.Size(), 0);
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
