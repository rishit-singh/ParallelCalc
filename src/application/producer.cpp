#include <calculator.hpp>
#include <kafka/kafka.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

/// @brief Operations to dispatch to the consumer
struct Operation
{
    /// @brief Action type
    std::string Action;

    /// @brief Left operand
    mpz_class Left;

    /// @brief Right operand
    mpz_class Right;

    /// @brief Converts the current object to json
    /// @return 
    json ToJson() const;
    
    Operation(std::string, mpz_class , mpz_class);
};

Operation::Operation(std::string action, mpz_class left, mpz_class right) 
    : Action(action), Left(left), Right(right) {}


json Operation::ToJson() const
{
    return {
        { "action", this->Action },
        { "left", this->Left.get_si() },
        { "right", this->Right.get_si() }
    };
}

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto basic_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(config.LogFile);
	
    std::vector<spdlog::sink_ptr> sinks{console_sink, basic_sink};
	
    auto logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

    KafkaProducer producer(KafkaConfig::FromFile(argv[1]), logger);

    // Dispatch calculator actions
    producer.Stream({
        Operation("ADD", 5, 5).ToJson().dump(),
        Operation("SUB", 5, 5).ToJson().dump(),
        Operation("MUL", 5, 5).ToJson().dump(),
        Operation("DIV", 5, 5).ToJson().dump(),
        Operation("FAC", 5, 5).ToJson().dump()
    });


    // while (true)
    // {
    //     std::string inp;
    //     std::cin >> inp;
    //     producer.Stream({ inp }); 
    // }
}

