namespace ParallelCalc
{
    /// @brief Calculator class with basic arithemic operations
    /// @tparam T Type of the operands
    template<typename T>     
    class Calculator
    {
    public:
        /// @brief Adds two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        T Add(T, T);

        /// @brief Subtracts two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        T Subtract(T, T);
        
        /// @brief Multiplies two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        T Multiply(T, T);
        
        /// @brief Divides two operands
        /// @param left Left operand
        /// @param right Right operand
        /// @return Operation result 
        T Divide(T, T);

        /// @brief Default construtor
        Calculator() = default;

        /// @brief Default destructor
        ~Calculator() = default;
    };
} 

template<typename T> 
T ParallelCalc::Calculator<T>::Add(T left, T right) 
{
    return left + right;
}

template<typename T> 
T ParallelCalc::Calculator<T>::Subtract(T left, T right) 
{
    return left - right;
}

template<typename T> 
T ParallelCalc::Calculator<T>::Multiply(T left, T right) 
{
    return left * right;
}

template<typename T> 
T ParallelCalc::Calculator<T>::Divide(T left, T right) 
{
    return left / right;
}