#include <calculator.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    ParallelCalc::Calculator<long long> calculator;

    std::cout << "a + b = " << calculator.Add(atoi(argv[1]), atoi(argv[2])) << '\n'
            << "a - b = " << calculator.Subtract(atoi(argv[1]), atoi(argv[2])) << '\n'
            << "a * b = " << calculator.Multiply(atoi(argv[1]), atoi(argv[2])) << '\n'
            << "a / b = " << calculator.Divide(atoi(argv[1]), atoi(argv[2])) << '\n';

    return 0;
}

