#include <cppkafka/producer.h> 
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>
#include <fstream>

using json = nlohmann::json;

using cppkafka::Producer;
using cppkafka::Configuration;
using cppkafka::Topic;
using cppkafka::MessageBuilder;

/// @brief Config for Kafka services
struct KafkaConfig
{   
    /// @brief Broker URL
    std::string Broker;

    /// @brief Topic to use 
    std::string Topic;

    /// @brief Topic partition
    size_t Partition;

    /// @brief Loads the config from a file 
    /// @param File path 
    /// @return Loaded config
    static KafkaConfig FromFile(const std::string_view);

    KafkaConfig(std::string_view = nullptr, std::string_view = nullptr, size_t = 0);
};

/// @brief Producer abstraction
class KafkaProducer
{
private:
    /// @brief Configuration 
    KafkaConfig Config;

    /// @brief Message builder
    MessageBuilder Builder;

    /// @brief Producer instance
    Producer mProducer;

public:
    /// @brief Streams the given messages to the broker
    /// @param messages to stream 
    void Stream(std::vector<std::string>);

    KafkaProducer(KafkaConfig);
};

