#include <cppkafka/producer.h> 
#include <cppkafka/cppkafka.h>
#include <cppkafka/configuration.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>
#include <fstream>
#include <csignal>
#include <functional>

using json = nlohmann::json;

using cppkafka::Producer;
using cppkafka::Configuration;
using cppkafka::Topic;
using cppkafka::MessageBuilder;
using cppkafka::Consumer;
using cppkafka::Message;

constexpr size_t DefaultPollDelay = 1000;

/// @brief Config for Kafka services
struct KafkaConfig
{   
    /// @brief Broker URL
    std::string Broker;

    /// @brief Topic to use 
    std::string Topic;

    /// @brief Topic partition
    size_t Partition;

    /// @brief Groupd Id for the consumer
    std::string GroupId;

    /// @brief Delay in ms for each call of each consumer poll
    size_t PollDelay;

    /// @brief File to write the logs to
    std::string LogFile;

    /// @brief Loads the config from a file 
    /// @param File path 
    /// @return Loaded config
    static KafkaConfig FromFile(const std::string_view);

    KafkaConfig(std::string = nullptr, std::string = nullptr, const size_t = 0, std::string = nullptr, const size_t = DefaultPollDelay, std::string = nullptr);
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

    /// @brief Pointer to a logger instance
    std::shared_ptr<spdlog::logger> Logger;

public:
    /// @brief Streams the given messages to the broker
    /// @param messages to stream 
    void Stream(std::vector<std::string>);

    KafkaProducer(KafkaConfig, std::shared_ptr<spdlog::logger> = nullptr);
};

/// @brief Consumer abstraction
class KafkaConsumer
{
private:
    /// @brief Configuration 
    KafkaConfig Config;
    
    /// @brief Consumer instance
    Consumer mConsumer;

    /// @brief Callback called when a message is received after polling
    std::function<void(const Message&)> OnReceiveCallback; 

    /// @brief Running state
    bool IsRunning;

    /// @brief Pointer to a logger instance
    std::shared_ptr<spdlog::logger> Logger;

public: 
    /// @brief Runs the consumer loop
    void Run();

    /// @brief Sets OnReceiveCallback to the given value 
    /// @param callback Callback to set  
    void SetOnReceiveCallback(std::function<void(const Message&)>);

    KafkaConsumer(KafkaConfig, std::shared_ptr<spdlog::logger> = nullptr);
};

