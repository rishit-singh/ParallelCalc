#include <gmpxx.h>

namespace ParallelCalc
{
    /// @brief Calculator class with basic arithemic operations
    class Calculator
    {
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

        /// @brief Default construtor
        Calculator() = default;

        /// @brief Default destructor
        ~Calculator() = default;
    };
} 

