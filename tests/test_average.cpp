#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "../include/common.h"

using ::testing::Eq;
using ::testing::DoubleEq;
using ::testing::DoubleNear;

class AverageTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    void runAverageThread(ThreadData& data) {
        #ifdef _WIN32
        HANDLE thread = CreateThread(NULL, 0, average_thread, &data, 0, NULL);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        #else
        pthread_t thread;
        pthread_create(&thread, NULL, average_thread, &data);
        pthread_join(thread, NULL);
        #endif
    }
};

TEST_F(AverageTest, CalculatesAverageOfPositiveNumbers) {
    std::vector<int> testArray = {2, 4, 6, 8, 10};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    
    runAverageThread(data);
    
    EXPECT_DOUBLE_EQ(data.average, 6.0);
}

TEST_F(AverageTest, CalculatesAverageOfNegativeNumbers) {
    std::vector<int> testArray = {-2, -4, -6, -8, -10};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    
    runAverageThread(data);
    
    EXPECT_DOUBLE_EQ(data.average, -6.0);
}

TEST_F(AverageTest, CalculatesAverageOfMixedNumbers) {
    std::vector<int> testArray = {-5, 0, 5, 10, -10};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    
    runAverageThread(data);
    
    EXPECT_DOUBLE_EQ(data.average, 0.0);
}

TEST_F(AverageTest, HandlesSingleElement) {
    std::vector<int> testArray = {42};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    
    runAverageThread(data);
    
    EXPECT_DOUBLE_EQ(data.average, 42.0);
}

TEST_F(AverageTest, HandlesLargeNumbers) {
    std::vector<int> testArray = {1000000, 2000000, 3000000};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    
    runAverageThread(data);
    
    EXPECT_DOUBLE_EQ(data.average, 2000000.0);
}

TEST_F(AverageTest, SetsCompletedFlag) {
    std::vector<int> testArray = {1, 2, 3};
    ThreadData data;
    data.array = testArray.data();
    data.size = testArray.size();
    data.average_completed = false;
    
    runAverageThread(data);
    
    EXPECT_TRUE(data.average_completed);
}
