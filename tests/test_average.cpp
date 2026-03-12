#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/common.h"

using ::testing::Eq;
using ::testing::DoubleEq;
using ::testing::DoubleNear;

class AverageTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(AverageTest, Placeholder) {
    EXPECT_TRUE(true);
}
