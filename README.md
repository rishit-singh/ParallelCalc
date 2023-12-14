# ParallelCalc
A C++20 based high perf multithreaded calculator compatible with Apache Kafka.

## Dependencies

### cppkafka
Used for streaming of batches of operations.
### googletest
Used for unit tests.
### spdlog 
Used for logging 
### GMP
Used for high precision numbers.

> All dependencies are fetched and built by the CMakeLists except GMP which needs to be installed separately.

## Build instructions

### Compiling
```
git clone https://github.com/rishit-singh/ParallelCalc.git;

cd ParallelCalc;

cmake -Bbuild && cd build;

make;
```

### Running

#### Configuration
All config should be placed in a json file in the following format:
```json
{
    "broker": "URL", /* broker url*/
    "topic": "some_topic", /* kafka topic*/
    "partition": 0, /* partion id */
    "group_id": "some_group", /* group id for the consumer */
    "poll_delay": 1, /* delay before each message poll on the consumer */
    "log_file": ".logs" /* file to write the logs to */
}
```

#### Producer
```
./ParallelProducer <json config file>
```
#### Consumer
```
./ParallelConsumer <json config file> <output file>
```
##### Tests
```
./test_basic
./test_factorial
```

### Kafka Abstraction API

The library provides a simple configurable abstraction of Kafka boilerplate that makes it easier to integrate streaming with the existing services, which in this case is the calculator.

#### KafkaProducer
```cpp
KafkaConfig config = KafkaConfig::FromFile("config.json"); // load the config

auto logger = make_shared<spdlog::logger>(...); // create a logger with the desired options

KafkaProducer producer(KafkaConfig::FromFile(argv[1]), logger); // create the producer

producer.Stream({
    "foobar",
    "fizzbuzz"
}); // stream the messages

```

#### KafkaConsumer
```cpp
KafkaConfig config = KafkaConfig::FromFile("config.json"); // load the config

auto logger = make_shared<spdlog::logger>(...); // create a logger with the desired options

KafkaConsumer consumer(KafkaConfig::FromFile(argv[1]), logger); // create the consumer


consumer.SetOnReceiveCallback([](const Message& message) {
    /// utilize the message
}); // set the callback to handle each message, called every poll

consumer.Run(); // run the consumer
```


 