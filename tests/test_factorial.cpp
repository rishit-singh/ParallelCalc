#include <gtest/gtest.h>
#include <calculator.hpp>

TEST(Factorial, FactorialTest)
{
    ParallelCalc::Calculator calculator;

    EXPECT_TRUE(calculator.Factorial(0) == 1);

    EXPECT_TRUE(calculator.Factorial(1) == 1);

    EXPECT_TRUE(calculator.Factorial(5) == 120);

    EXPECT_TRUE(calculator.Factorial(10) == 3628800);

    EXPECT_TRUE(calculator.Factorial(15) == 1307674368000);
}
 