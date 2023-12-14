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

<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="831px" height="286px" viewBox="-0.5 -0.5 831 286" content="&lt;mxfile host=&quot;app.diagrams.net&quot; modified=&quot;2023-12-14T03:35:28.561Z&quot; agent=&quot;Mozilla/5.0 (X11; Linux x86_64; rv:120.0) Gecko/20100101 Firefox/120.0&quot; etag=&quot;brYZZPiUp6MOOw05mpUc&quot; version=&quot;22.1.8&quot; type=&quot;device&quot;&gt;&#xA;  &lt;diagram name=&quot;Page-1&quot; id=&quot;RzNcLbMmKyP_g5sOaSQG&quot;&gt;&#xA;    &lt;mxGraphModel dx=&quot;1434&quot; dy=&quot;755&quot; grid=&quot;1&quot; gridSize=&quot;10&quot; guides=&quot;1&quot; tooltips=&quot;1&quot; connect=&quot;1&quot; arrows=&quot;1&quot; fold=&quot;1&quot; page=&quot;1&quot; pageScale=&quot;1&quot; pageWidth=&quot;850&quot; pageHeight=&quot;1100&quot; math=&quot;0&quot; shadow=&quot;0&quot;&gt;&#xA;      &lt;root&gt;&#xA;        &lt;mxCell id=&quot;0&quot; /&gt;&#xA;        &lt;mxCell id=&quot;1&quot; parent=&quot;0&quot; /&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-3&quot; value=&quot;Broker&quot; style=&quot;rounded=1;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;350&quot; y=&quot;190&quot; width=&quot;250&quot; height=&quot;230&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-7&quot; value=&quot;operations&quot; style=&quot;rounded=0;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;407.5&quot; y=&quot;320&quot; width=&quot;135&quot; height=&quot;80&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-4&quot; style=&quot;edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;exitX=1;exitY=0.5;exitDx=0;exitDy=0;entryX=0;entryY=0.5;entryDx=0;entryDy=0;&quot; edge=&quot;1&quot; parent=&quot;1&quot; source=&quot;BYEm4YZsF7wP3u-vwrFF-1&quot; target=&quot;BYEm4YZsF7wP3u-vwrFF-8&quot;&gt;&#xA;          &lt;mxGeometry relative=&quot;1&quot; as=&quot;geometry&quot;&gt;&#xA;            &lt;mxPoint x=&quot;170&quot; y=&quot;285&quot; as=&quot;sourcePoint&quot; /&gt;&#xA;          &lt;/mxGeometry&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-1&quot; value=&quot;KafkaProducer&quot; style=&quot;rounded=0;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;20&quot; y=&quot;350&quot; width=&quot;150&quot; height=&quot;60&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-5&quot; value=&quot;{ &amp;quot;action&amp;quot;: &amp;quot;ADD&amp;quot;, &amp;quot;left&amp;quot;: 5, &amp;quot;right&amp;quot;: 5}&quot; style=&quot;shape=process;whiteSpace=wrap;html=1;backgroundOutline=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;190&quot; y=&quot;390&quot; width=&quot;150&quot; height=&quot;60&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-11&quot; style=&quot;edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;exitX=1;exitY=0.5;exitDx=0;exitDy=0;&quot; edge=&quot;1&quot; parent=&quot;1&quot; source=&quot;BYEm4YZsF7wP3u-vwrFF-8&quot; target=&quot;BYEm4YZsF7wP3u-vwrFF-10&quot;&gt;&#xA;          &lt;mxGeometry relative=&quot;1&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-8&quot; value=&quot;Partition #0&quot; style=&quot;rounded=0;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;415&quot; y=&quot;370&quot; width=&quot;120&quot; height=&quot;20&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-9&quot; style=&quot;edgeStyle=orthogonalEdgeStyle;rounded=0;orthogonalLoop=1;jettySize=auto;html=1;exitX=0.5;exitY=1;exitDx=0;exitDy=0;&quot; edge=&quot;1&quot; parent=&quot;1&quot; source=&quot;BYEm4YZsF7wP3u-vwrFF-8&quot; target=&quot;BYEm4YZsF7wP3u-vwrFF-8&quot;&gt;&#xA;          &lt;mxGeometry relative=&quot;1&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-10&quot; value=&quot;KafkaConsumer&quot; style=&quot;rounded=0;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;660&quot; y=&quot;285&quot; width=&quot;190&quot; height=&quot;190&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;        &lt;mxCell id=&quot;BYEm4YZsF7wP3u-vwrFF-12&quot; value=&quot;Calculator&quot; style=&quot;rounded=0;whiteSpace=wrap;html=1;&quot; vertex=&quot;1&quot; parent=&quot;1&quot;&gt;&#xA;          &lt;mxGeometry x=&quot;695&quot; y=&quot;410&quot; width=&quot;120&quot; height=&quot;40&quot; as=&quot;geometry&quot; /&gt;&#xA;        &lt;/mxCell&gt;&#xA;      &lt;/root&gt;&#xA;    &lt;/mxGraphModel&gt;&#xA;  &lt;/diagram&gt;&#xA;&lt;/mxfile&gt;&#xA;"><defs/><g><rect x="330" y="0" width="250" height="230" rx="34.5" ry="34.5" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 248px; height: 1px; padding-top: 115px; margin-left: 331px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Broker</div></div></div></foreignObject><text x="455" y="119" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Broker</text></switch></g><rect x="387.5" y="130" width="135" height="80" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 133px; height: 1px; padding-top: 170px; margin-left: 389px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">operations</div></div></div></foreignObject><text x="455" y="174" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">operations</text></switch></g><path d="M 150 190 L 388.63 190" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 393.88 190 L 386.88 193.5 L 388.63 190 L 386.88 186.5 Z" fill="rgb(0, 0, 0)" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><rect x="0" y="160" width="150" height="60" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 148px; height: 1px; padding-top: 190px; margin-left: 1px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">KafkaProducer</div></div></div></foreignObject><text x="75" y="194" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">KafkaProducer</text></switch></g><rect x="170" y="200" width="150" height="60" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><path d="M 185 200 L 185 260 M 305 200 L 305 260" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 230px; margin-left: 186px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">{ "action": "ADD", "left": 5, "right": 5}</div></div></div></foreignObject><text x="245" y="234" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">{ "action": "ADD", "...</text></switch></g><path d="M 515 190 L 633.63 190" fill="none" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="stroke"/><path d="M 638.88 190 L 631.88 193.5 L 633.63 190 L 631.88 186.5 Z" fill="rgb(0, 0, 0)" stroke="rgb(0, 0, 0)" stroke-miterlimit="10" pointer-events="all"/><rect x="395" y="180" width="120" height="20" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 190px; margin-left: 396px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Partition #0</div></div></div></foreignObject><text x="455" y="194" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Partition #0</text></switch></g><rect x="640" y="95" width="190" height="190" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 188px; height: 1px; padding-top: 190px; margin-left: 641px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">KafkaConsumer</div></div></div></foreignObject><text x="735" y="194" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">KafkaConsumer</text></switch></g><rect x="675" y="220" width="120" height="40" fill="rgb(255, 255, 255)" stroke="rgb(0, 0, 0)" pointer-events="all"/><g transform="translate(-0.5 -0.5)"><switch><foreignObject style="overflow: visible; text-align: left;" pointer-events="none" width="100%" height="100%" requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"><div xmlns="http://www.w3.org/1999/xhtml" style="display: flex; align-items: unsafe center; justify-content: unsafe center; width: 118px; height: 1px; padding-top: 240px; margin-left: 676px;"><div style="box-sizing: border-box; font-size: 0px; text-align: center;" data-drawio-colors="color: rgb(0, 0, 0); "><div style="display: inline-block; font-size: 12px; font-family: Helvetica; color: rgb(0, 0, 0); line-height: 1.2; pointer-events: all; white-space: normal; overflow-wrap: normal;">Calculator</div></div></div></foreignObject><text x="735" y="244" fill="rgb(0, 0, 0)" font-family="Helvetica" font-size="12px" text-anchor="middle">Calculator</text></switch></g></g><switch><g requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility"/><a transform="translate(0,-5)" xlink:href="https://www.drawio.com/doc/faq/svg-export-text-problems" target="_blank"><text text-anchor="middle" font-size="10px" x="50%" y="100%">Text is not SVG - cannot display</text></a></switch></svg>

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


 