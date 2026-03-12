#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/common.h"

using ::testing::Eq;
using ::testing::Le;
using ::testing::Ge;

class MinMaxTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MinMaxTest, Placeholder) {
    EXPECT_TRUE(true);
}
