#include <calculator.hpp>

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