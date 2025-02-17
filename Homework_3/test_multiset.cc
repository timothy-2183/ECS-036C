#include <gtest/gtest.h>

#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset<int> mset;

  /* Should be fully empty */
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey) {
  Multiset<int> mset;

  /* Test some insertion */
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}
// Test fixture class to set up a common environment
class MultisetTest : public ::testing::Test {
  protected:
      // Multiset instance to be used in tests
      Multiset<int> multiset;
  
      // SetUp() can be used to initialize objects before each test
      void SetUp() override {
          multiset.Insert(10);
          multiset.Insert(20);
          multiset.Insert(20);
          multiset.Insert(30);
          multiset.Insert(30);
          multiset.Insert(30);
      }
  
      // TearDown() can be used to clean up after each test if needed
      void TearDown() override {
          // Cleanup, if needed (e.g., resetting values)
      }
  };
  
  // Test for inserting elements
  TEST_F(MultisetTest, Insertion) {
      EXPECT_EQ(multiset.Size(), 6);
      EXPECT_TRUE(multiset.Contains(20));
      EXPECT_TRUE(multiset.Contains(30));
      EXPECT_FALSE(multiset.Contains(25));
  }
  
  // Test for counting occurrences of elements
  TEST_F(MultisetTest, CountElements) {
      EXPECT_EQ(multiset.Count(20), 2);  // 20 occurs twice
      EXPECT_EQ(multiset.Count(30), 3);  // 30 occurs three times
      EXPECT_THROW(multiset.Count(25), std::runtime_error);  // 25 does not exist, should throw an exception
  }
  
  // Test for Min and Max elements
  TEST_F(MultisetTest, MinMaxElements) {
      EXPECT_EQ(multiset.Min(), 10);  // Min element should be 10
      EXPECT_EQ(multiset.Max(), 30);  // Max element should be 30
  }
  
  // Test for Floor and Ceil methods
  TEST_F(MultisetTest, FloorCeil) {
      EXPECT_EQ(multiset.Floor(25), 20);  // Floor of 25 should be 20
      EXPECT_EQ(multiset.Ceil(25), 30);   // Ceil of 25 should be 30
  }
  
  // Test for removing elements
  TEST_F(MultisetTest, RemoveElements) {
      multiset.Remove(20);  // Remove one occurrence of 20
      EXPECT_EQ(multiset.Size(), 5);  // Size should decrease
      EXPECT_TRUE(multiset.Contains(20));  // 20 should still exist
      EXPECT_EQ(multiset.Count(20), 1);  // Only 1 occurrence left
  
      // Remove all occurrences of 30
      multiset.Remove(30);  // Remove one occurrence of 30
      multiset.Remove(30);  // Remove another occurrence of 30
      EXPECT_EQ(multiset.Size(), 3);  // Size should now be 3
  
      // After removing all 30s, the multiset should not contain 30
      EXPECT_FALSE(multiset.Contains(30));
      EXPECT_THROW(multiset.Count(30), std::runtime_error);  // Should throw exception when trying to count 30
  }
  
  // Test for handling empty multiset
  TEST_F(MultisetTest, EmptyMultiset) {
      Multiset<int> emptySet;
      EXPECT_TRUE(emptySet.Empty());  // The set should be empty initially
      EXPECT_THROW(emptySet.Min(), std::runtime_error);  // Min should throw exception on empty set
      EXPECT_THROW(emptySet.Max(), std::runtime_error);  // Max should throw exception on empty set
  }

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

