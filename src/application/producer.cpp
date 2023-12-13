#include <kafka/kafka.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char** argv)
{
    KafkaConfig config = KafkaConfig::FromFile(argv[1]);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto basic_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(config.LogFile);
	
    std::vector<spdlog::sink_ptr> sinks{console_sink, basic_sink};
	
    auto logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

    KafkaProducer producer(KafkaConfig::FromFile(argv[1]), logger);
    
    while (true)
    {
        std::string inp;
        std::cin >> inp;
        producer.Stream({ inp }); 
    }
}
