#include <gmpxx.h>
#include <map>
#include <mutex>
#include <thread>

namespace ParallelCalc
{
    /// @brief Calculator class with basic arithemic operations
    class Calculator
    {
    private:
        /// @brief Threshold for when to use a lookup table for memoization 
        static constexpr int32_t LookupThreshold = 1000;
    protected:
        /// @brief Final factorial result
        mpz_class FactorialResult { 1 };
        
        std::mutex FactorialResultMutex; 

        /// @brief Map for upperbound memoization
        std::map<mpz_class, mpz_class> FactorialMap;

        // /// @brief Lookup table for lowerbound memoization
        // std::unordered_map<mpz_class, mpz_class> FactorialLookup;

        /// @brief Ranged factorial function for a single thread
        /// @param start Start of the range 
        /// @param end End of the range
        /// @return Factorial result
        mpz_class FactorialSingle(const mpz_class&, const mpz_class& );

        /// @brief Parent function to FactorialSingle to calculate factorial using multiple managed threads
        /// @param start Start of the range 
        /// @param end End of the range
        /// @return Factorial result
        mpz_class FactorialParallel(const mpz_class&, const mpz_class&);

        /// @brief Threads to execute factorial in
        std::vector<std::thread> FactorialThreadPool;    
    public:
        /// @brief Adds two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        mpz_class Add(const mpz_class&, const mpz_class&);

        /// @brief Subtracts two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        mpz_class Subtract(const mpz_class&, const mpz_class&);
        
        /// @brief Multiplies two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        mpz_class Multiply(const mpz_class&, const mpz_class&);
        
        /// @brief Divides two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        mpz_class Divide(const mpz_class&, const mpz_class&);

        /// @brief Calculates the factorial of the given number 
        /// @param num Number to calculate the factorial of
        /// @return Factorial result
        mpz_class Factorial(const mpz_class&);

        /// @brief Default construtor
        Calculator() = default;

        /// @brief Default destructor
        ~Calculator() = default;
    };
} 

