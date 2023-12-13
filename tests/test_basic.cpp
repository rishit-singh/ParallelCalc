#include <gtest/gtest.h>
#include <calculator.hpp>

TEST(Basic, BasicAssertions)
{
    ParallelCalc::Calculator calculator;
    
    EXPECT_TRUE(calculator.Add(50, 65) == 115);
    EXPECT_TRUE(calculator.Subtract(340, 70) == 270);
    EXPECT_TRUE(calculator.Multiply(500, 6) == 3000);
    EXPECT_TRUE(calculator.Divide(156, 13) == 12);
}
 