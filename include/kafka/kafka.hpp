// #include <cppkafka/cppkafka.h>
// #include <cppkafka/configuration.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <fstream>

using json = nlohmann::json;

/// @brief Config for Kafka services
struct KafkaConfig
{   
    /// @brief Broker URL
    std::string_view Broker;

    /// @brief Topic to use 
    std::string_view Topic;

    /// @brief Topic partition
    std::string_view Partition;

    /// @brief Loads the config from a file 
    /// @param File path 
    /// @return Loaded config
    static KafkaConfig FromFile(const std::string_view);

    KafkaConfig(std::string_view = nullptr, std::string_view = nullptr, std::string_view = nullptr);
};
