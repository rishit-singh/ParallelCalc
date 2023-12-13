#include <calculator.hpp>
#include <iostream>
#include <kafka/kafka.hpp>

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    std::cout << config.Broker << " " << config.Topic << " "<< config.Partition << "\n";

    // ParallelCalc::Calculator calculator;

    // std::cout << "a + b = " << (calculator.Add(atoi(argv[1]), atoi(argv[2]))).get_str() << '\n'
    //         << "a - b = " << calculator.Subtract(atoi(argv[1]), atoi(argv[2])).get_str() << '\n'
    //         << "a * b = " << calculator.Multiply(atoi(argv[1]), atoi(argv[2])).get_str() << '\n'
    //         << "a / b = " << calculator.Divide(atoi(argv[1]), atoi(argv[2])).get_str() << '\n'
    //         << "Factorial: " << calculator.Factorial(atoi(argv[3])).get_str() << '\n';

    return 0;
}

