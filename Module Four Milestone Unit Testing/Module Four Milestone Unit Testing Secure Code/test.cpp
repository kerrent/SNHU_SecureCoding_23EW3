// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// DONE: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// DONE: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    //Verify the collection starts at size 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    //Verify the collection is size 5 after 5 entries are entered.
    ASSERT_EQ(collection->size(), 5);

}

// DONE: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanCurrentSize)
{
    //Verify the collection starts at size 0
    ASSERT_EQ(collection->size(), 0);

    //Verify max size is greater than 0 with 0 entries.
    ASSERT_GT(collection->max_size(), collection->size());
    
    //Add one entry
    add_entries(1);

    //Verify max size is greater than 1 with 1 entries.
    ASSERT_GT(collection->max_size(), collection->size());

    //Add 4 more entries to bring the number to 5
    add_entries(4);

    //Verify max size is greater than 5 with 5 entries.
    ASSERT_GT(collection->max_size(), collection->size());

    //Add 5 more entries bringing the total to 10.
    add_entries(5);

    //Verify max size is greater than 10 with 10 entries.
    ASSERT_GT(collection->max_size(), collection->size());
}

// DONE: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityEqualOrGreaterThanCurrentSize)
{
    //Verify the collection starts at size 0
    ASSERT_EQ(collection->size(), 0);

    //Verify capacity is greater than or equal to size with 0 entries.
    ASSERT_GE(collection->capacity(), collection->size());

    //Add one entry
    add_entries(1);

    //Verify capacity is greater than or equal to size with 1 entries.
    ASSERT_GE(collection->capacity(), collection->size());

    //Add 4 more entries to bring the number to 5
    add_entries(4);

    //Verify capacity is greater than or equal to size with 5 entries.
    ASSERT_GE(collection->capacity(), collection->size());

    //Add 5 more entries bringing the total to 10.
    add_entries(5);

    //Verify capacity is greater than or equal to size with 10 entries.
    ASSERT_GE(collection->capacity(), collection->size());
}

// DONE: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CanIncreaseSizeUsingResize)
{
    //Verify the collection starts at size 0
    ASSERT_EQ(collection->size(), 0);

    //Use resize to increase the size of the collection
    collection->resize(10);

    //Verify the collection is increased to size 10 after the resize.
    ASSERT_EQ(collection->size(), 10);
}

// DONE: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CanDecreaseSizeUsingResize)
{
    add_entries(5);

    //Verify the collection is size 5 after adding entries
    ASSERT_EQ(collection->size(), 5);

    //Use resize to decrease the size of the collection
    collection->resize(3);

    //Verify the collection is decreased to size 3 after the resize.
    ASSERT_EQ(collection->size(), 3);
}

// DONE: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CanDecreaseSizeToZeroUsingResize)
{
    add_entries(5);

    //Verify the collection is size 5 after adding entries
    ASSERT_EQ(collection->size(), 5);

    //Use resize to decrease the size of the collection to 0
    collection->resize(0);

    //Verify the collection is decreased to size 0 after the resize.
    ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify clear erases the collection
TEST_F(CollectionTest, CanEraseUsingClear)
{
    add_entries(5);

    //Verify the collection is size 5 after 5 entries are entered.
    ASSERT_EQ(collection->size(), 5);

    //Call clear to erase the collection.
    collection->clear();

    //Verify collection is empty after clear is called.
    ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CanEraseAll)
{
    add_entries(5);

    //Verify the collection is size 5 after 5 entries are entered.
    ASSERT_EQ(collection->size(), 5);

    //Call erase from the beginning to the end of the collection.
    collection->erase(collection->begin(), collection->end());

    //Verify collection is empty after erasing from the beginning to the end.
    ASSERT_EQ(collection->size(), 0);
}

// DONE: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    add_entries(5);

    //Verify the collection is size 5 after 5 entries are entered.
    ASSERT_EQ(collection->size(), 5);

    //Get the current capacity.
    int currentCapacity = collection ->capacity();

    //Use reserve to increase capacity by 1
    collection->reserve(currentCapacity + 1);

    //Verify collection size is still 5
    ASSERT_EQ(collection->size(), 5);

    //Verify collection capacity has increased.
    ASSERT_GT(collection->capacity(), currentCapacity);
}

// DONE: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, ThrowExceptionWhenAtBeyondBounds)
{
    //Verify the collection is size 0 
    ASSERT_EQ(collection->size(), 0);

    //Verify an std::out_of_range exception is is thrown when we call at() with an out of bounds index.
    ASSERT_THROW(collection->at(5), std::out_of_range);

}

// DONE: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
//Positive Test
//Verify pop_back reduces the size by 1.
TEST_F(CollectionTest, PopBackReducesSize)
{
    add_entries(5);

    //Verify the collection is size 5 after 5 entries are entered.
    ASSERT_EQ(collection->size(), 5);

    //Use pop_back to remove the last element.
    collection->pop_back();

    //Verify collection size is now 4
    ASSERT_EQ(collection->size(), 4);
}

//Negative Test
//Verify reserve throws an exception when reserving greater than max_size.
TEST_F(CollectionTest, ReserveThrowsExceptionIfOverMaxSize)
{
    add_entries(5);

    //Verify the collection is size 5
    ASSERT_EQ(collection->size(), 5);

    //Verify an exception is thrown when reserving greater than max_size.
    ASSERT_ANY_THROW(collection->reserve(collection->max_size() + 1));           
}