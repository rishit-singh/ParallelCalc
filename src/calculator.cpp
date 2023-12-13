#include <calculator.hpp>
#include <iostream>

mpz_class ParallelCalc::Calculator::Add(const mpz_class& left, const mpz_class& right) 
{
    return left + right;
}

mpz_class ParallelCalc::Calculator::Subtract(const mpz_class& left, const mpz_class& right) 
{
    return left - right;
}

mpz_class ParallelCalc::Calculator::Multiply(const mpz_class& left, const mpz_class& right) 
{
    return left * right;
}

mpz_class ParallelCalc::Calculator::Divide(const mpz_class& left, const mpz_class& right) 
{
    return left / right;
}

mpz_class ParallelCalc::Calculator::FactorialSingle(const mpz_class& start, const mpz_class& end)
{
    mpz_class result = start, end_final = end;

    if (end == 0)
        end_final  = 1;

    for (mpz_class x = start - 1; x >= end_final; x--) 
        result *= (x);

    std::lock_guard<std::mutex> lock(this->FactorialResultMutex); // lock the mutex before modifying the shared result

    this->FactorialResult *= result;

    return result;
}

mpz_class ParallelCalc::Calculator::Factorial(const mpz_class& number)
{
    this->FactorialResult = 1;

    const size_t numThreads = std::thread::hardware_concurrency();

    mpz_class chunkSize = number / numThreads; // get chunk size based on the available system threads

    if (chunkSize == 0)
        chunkSize = 1;

    this->FactorialThreadPool.clear();
    this->FactorialThreadPool.reserve(numThreads);

    size_t index = 0;

    for (mpz_class x = number; x > 1; x -= chunkSize)
    {
        mpz_class start = x, end = x - chunkSize;

        if (end < 0)
            end = 1;

        if (x != number)
            start = x - 1; 

        this->FactorialThreadPool.emplace_back(&Calculator::FactorialSingle, this, start, end);
    }

    for (auto& t : FactorialThreadPool) // join the threads once all parts are calculated
        t.join();

    return this->FactorialResult;
}
