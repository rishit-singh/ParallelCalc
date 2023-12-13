#include "kafka.hpp"

KafkaConfig::KafkaConfig(std::string_view broker, std::string_view topic, size_t partition)
    : Broker(broker), Topic(topic), Partition(partition)
{
}

KafkaConfig KafkaConfig::FromFile(const std::string_view file)
{
    std::ifstream fp(file.data());

    std::array<std::string_view, 3> requiredKeys = {
        "broker",
        "topic",
        "partition"
    }; 

    json data = json::parse(fp);

    for (auto key : requiredKeys)
        if (!data.contains(key.data()))
        {
            std::string error = std::string(key);
            throw std::runtime_error(error + " is required but not provided in the config.");
        }

    return KafkaConfig(data["broker"].template get<std::string_view>(), data["topic"].template get<std::string_view>(), static_cast<size_t>(data["partition"])); 
}

    

KafkaProducer::KafkaProducer(KafkaConfig config) : Config(config), Builder(config.Topic), mProducer({
                { "metadata.broker.list", config.Broker }
        })
        {
        }

void KafkaProducer::Stream(std::vector<std::string> messages)
{
    for (auto message : messages)
    {   
        this->Builder.payload(message);
        this->mProducer.produce(this->Builder);
    }

    this->mProducer.flush();
}