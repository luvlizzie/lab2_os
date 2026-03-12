#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <climits>
#include "../include/common.h"

using ::testing::Eq;
using ::testing::Le;
using ::testing::Ge;

class MinMaxTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    void runMinMaxThread(ThreadData& data) {
        #ifdef _WIN32
        HANDLE thread = CreateThread(NULL, 0, min_max_thread, &data, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        #else
        pthread_t thread;
        pthread_create(&thread, NULL, min_max_thread, &data);
        pthread_join(thread, NULL);
        #endif
    }
};

TEST_F(MinMaxTest, FindsMinAndMaxInPositiveArray) {
    std::vector<int> testArray = {5, 2, 8, 1, 9, 3};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.min = INT_MAX;
    data.max = INT_MIN;
    
    runMinMaxThread(data);
    
    EXPECT_EQ(data.min, 1);
    EXPECT_EQ(data.max, 9);
}

TEST_F(MinMaxTest, FindsMinAndMaxInNegativeArray) {
    std::vector<int> testArray = {-5, -2, -8, -1, -9, -3};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.min = INT_MAX;
    data.max = INT_MIN;
    
    runMinMaxThread(data);
    
    EXPECT_EQ(data.min, -9);
    EXPECT_EQ(data.max, -1);
}

TEST_F(MinMaxTest, HandlesSingleElementArray) {
    std::vector<int> testArray = {42};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.min = INT_MAX;
    data.max = INT_MIN;
    
    runMinMaxThread(data);
    
    EXPECT_EQ(data.min, 42);
    EXPECT_EQ(data.max, 42);
}

TEST_F(MinMaxTest, HandlesIdenticalElements) {
    std::vector<int> testArray = {7, 7, 7, 7, 7};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.min = INT_MAX;
    data.max = INT_MIN;
    
    runMinMaxThread(data);
    
    EXPECT_EQ(data.min, 7);
    EXPECT_EQ(data.max, 7);
}

TEST_F(MinMaxTest, SetsCompletedFlag) {
    std::vector<int> testArray = {1, 2, 3};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.min_max_completed = false;
    
    runMinMaxThread(data);
    
    EXPECT_TRUE(data.min_max_completed);
}
