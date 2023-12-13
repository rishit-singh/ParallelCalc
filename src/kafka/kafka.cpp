#include "kafka.hpp"

KafkaConfig::KafkaConfig(std::string broker, std::string topic, const size_t partition, std::string groupId, const size_t pollDelay)
    : Broker(broker), Topic(topic), Partition(partition), GroupId(groupId), PollDelay(pollDelay)
{
}

KafkaConfig KafkaConfig::FromFile(const std::string_view file)
{
    std::ifstream fp(file.data());

    std::array<std::string_view, 5> requiredKeys = {
        "broker",
        "topic",
        "partition",
        "group_id",
        "poll_delay"
    }; 

    json data = json::parse(fp);

    for (auto key : requiredKeys)
        if (!data.contains(key.data()))
        {
            std::string error = std::string(key);
            throw std::runtime_error(error + " is required but not provided in the config.");
        }

    return KafkaConfig(data["broker"].template get<std::string>(), 
                        data["topic"].template get<std::string>(),
                        data["partition"].template get<size_t>(),
                        data["group_id"].template get<std::string>(),
                        data["poll_delay"].template get<size_t>()); 
}

    

KafkaProducer::KafkaProducer(KafkaConfig config) : Config(config), Builder(config.Topic), mProducer({
                { "metadata.broker.list", config.Broker }
        })
        {
            this->Builder.partition(config.Partition);
        }

void KafkaProducer::Stream(std::vector<std::string> messages)
{
    for (auto message : messages)
    {  

        this->Builder.payload(message);
        std::cout << message << "\n";
        this->mProducer.produce(this->Builder);
    }

    this->mProducer.flush();
}


KafkaConsumer::KafkaConsumer(KafkaConfig config) 
    : Config(config), mConsumer({
                { "metadata.broker.list", config.Broker },
                { "group.id", config.GroupId },
                { "enable.auto.commit", false }
        }), IsRunning(false)
{
    // signal(SIGINT, [this](int) { this->IsRunning = false; });

    	// Print the assigned partitions on assignment
	this->mConsumer.set_assignment_callback(
		[](const cppkafka::TopicPartitionList& partitions) {
			std::stringstream ss("Got assigned: ");
			ss << partitions;


            std::cout << ss.str();
			// logger->info(ss.str());
		});

    this->mConsumer.set_revocation_callback([](const cppkafka::TopicPartitionList& partitions) {

			std::stringstream ss("Got revoked: ");
			ss << partitions;

            std::cout << ss.str();
		});
}


void KafkaConsumer::Run()
{
    this->mConsumer.subscribe({this->Config.Topic});

    this->IsRunning = true;

    while (this->IsRunning)
    {
        Message message = this->mConsumer.poll(std::chrono::milliseconds{this->Config.PollDelay});

        this->OnReceiveCallback(message);
    }
}

void KafkaConsumer::SetOnReceiveCallback(std::function<void(const Message&)> callback)
{
    this->OnReceiveCallback = callback;
}
