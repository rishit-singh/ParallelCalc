#include <kafka/kafka.hpp>

int main(int argc, char** argv)
{
    KafkaProducer producer(KafkaConfig::FromFile(argv[1]));
    
    while (true)
    {
        std::string inp;
        std::cin >> inp;
        producer.Stream({ inp }); 
    }
}
