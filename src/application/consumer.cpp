#include <calculator.hpp>
#include <kafka/kafka.hpp>
#include <fstream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

void HandleDispatch(json dispatch, ParallelCalc::Calculator& calculator, std::shared_ptr<spdlog::logger> logger, std::string_view outFile)
{
    const std::string operation = dispatch["action"].template get<std::string>();

    mpz_class result;

    std::ofstream stream(outFile.data(), std::ios::app);

    std::stringstream ss;

    if (operation == "ADD")
    {
        mpz_class left = dispatch["left"].template get<int>(),
            right = dispatch["right"].template get<int>();

        result = calculator.Add(left, right); 

        ss << operation << " " << left.get_str() << " " << right.get_str() << " " << result.get_str() << '\n';
    } 
    else if (operation == "SUB")
    {
        mpz_class left = dispatch["left"].template get<int>(),
            right = dispatch["right"].template get<int>();

        result = calculator.Subtract(left, right); 

        ss << operation << " " << left.get_str() << " " << right.get_str() << " " << result.get_str() << '\n';
    }
    else if (operation == "MUL")
    {
        mpz_class left = dispatch["left"].template get<int>(),
            right = dispatch["right"].template get<int>();

        result = calculator.Multiply(left, right); 

        ss << operation << " " << left.get_str() << " " << right.get_str() << " " << result.get_str() << '\n';
    }  
    else if (operation == "DIV")
    {
        mpz_class left = dispatch["left"].template get<int>(),
            right = dispatch["right"].template get<int>();

        result = calculator.Divide(left, right); 

        ss << operation << " " << left.get_str() << " " << right.get_str() << " " << result.get_str() << '\n';
    }  
    else if (operation == "FAC")
    {
        mpz_class num = dispatch["left"].template get<int>();

        result = calculator.Factorial(num); 

        ss << operation << " " << num.get_str() << " " << result.get_str() << '\n';
    } 

    std::string log = ss.str();

    logger->info(log);

    stream << log;

    stream.flush();
    stream.close(); 
    ss.flush();
}

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto basic_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(config.LogFile);
	
    std::vector<spdlog::sink_ptr> sinks{console_sink, basic_sink};
	
    auto logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());
    
    KafkaConsumer consumer(KafkaConfig::FromFile(argv[1]), logger);

    ParallelCalc::Calculator calculator;

    std::string_view outputFile = argv[2];

    consumer.SetOnReceiveCallback([logger, &calculator, &outputFile](const Message& message) {
        std::stringstream stream; 
        std::string str;

        stream << message.get_payload();

        try
        {
            HandleDispatch(json::parse(str = stream.str()), calculator, logger, outputFile);
        } 
        catch (std::exception& e) 
        {
            std::string error = "Exception occured: ";

            error.append(e.what())
                .append("\n"); 

            logger->critical(error);
        }
    });

    consumer.Run();
}