#include <gtest/gtest.h>
#include <calculator.hpp>

TEST(Basic, BasicAssertions)
{
    ParallelCalc::Calculator<int> calculator;
    
    EXPECT_EQ(calculator.Add(50, 65), 115);
    EXPECT_EQ(calculator.Subtract(340, 70), 270);
    EXPECT_EQ(calculator.Multiply(500, 6), 3000);
    EXPECT_EQ(calculator.Divide(156, 13), 12);
}
