#include <gtest/gtest.h>
#include "linkedlist.h"

TEST(List, List)
{
    ListDoublyLinked<int> l;
    ASSERT_EQ(l.Size(), 0);
    /* Test some exceptions */
    ASSERT_THROW(l.Get(1), std::out_of_range);
    ASSERT_THROW(l.Remove(0), std::out_of_range);
    ASSERT_THROW(l.Insert(1, 1), std::out_of_range);
    /* Insert item */
    l.Insert(23, 0);
    ASSERT_EQ(l.Size(), 1);
    ASSERT_EQ(l.Get(0), 23);
    /* Insert item at the back */
    l.Insert(42, l.Size());
    ASSERT_EQ(l.Size(), 2);
    ASSERT_EQ(l.Get(0), 23);
    ASSERT_EQ(l.Get(1), 42);
    /* Insert item at the front */
    l.Insert(99, 0);
    ASSERT_EQ(l.Size(), 3);
    ASSERT_EQ(l.Get(0), 99);
    ASSERT_EQ(l.Get(1), 23);
    ASSERT_EQ(l.Get(2), 42);
    /* Find values */
    ASSERT_EQ(l.Find(42), 2);
    ASSERT_EQ(l.Find(0), -1);
    /* Try to grow */
    l.Insert(1, l.Size());
    ASSERT_EQ(l.Size(), 4);
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}