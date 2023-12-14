# ParallelCalc
A C++20 based high perf multithreaded calculator compatible with Apache Kafka.

## How does it work? 

The application consists of two elements, the **Calculator** and the **Kafka streams**. 

### Calculator

The Calculator is a multithreaded class that can perform all basic arithematic operations on two high precision big integers. The special thing about it is that it optimized the factorial calculation by splitting the input into smaller ranges and then leveraging the available threads on the system to calculate factorials on each of those ranges. Each thread writes its factorial result to a shared result protected by mutex locks.


### Kafka streams

The application utilizes Kafka's producers and consumers to performing Calculator operations on streams. The producer dispatches operations in form of JSON strings like following: 
```json 
{"action":"MUL","left":5,"right":5} /* dispatches multiplication of 5 by 5*/

{"action":"FAC","left":5} /* dispatches factorial of 5*/
```

The consumer then processes these dispatches when they're received and uses the Calculator class to perform the requested operation on the provided operands.

Calculator currently supports the following opertions
```
ADD - Add two big ints.
SUB - Subtract a big int from another.
MUL - Multiply two big ints.
DIV - Divide a big int with another.
FAC - Calculate the factorial for a big int.

```

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


 