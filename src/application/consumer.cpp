#include <kafka/kafka.hpp>

int main(int argc, char** argv)
{
    KafkaConsumer consumer(KafkaConfig::FromFile(argv[1]));

    consumer.SetOnReceiveCallback([](const Message& message){
        if (message)
          std::cout << message.get_payload() << "\n";
    });

    consumer.Run();
}