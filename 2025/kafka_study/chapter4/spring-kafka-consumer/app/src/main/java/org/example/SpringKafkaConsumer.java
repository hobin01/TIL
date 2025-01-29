package org.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.annotation.PartitionOffset;
import org.springframework.kafka.annotation.TopicPartition;

@SpringBootApplication
public class SpringKafkaConsumer {
    public static Logger logger = LoggerFactory.getLogger(SpringKafkaConsumer.class);

    private static final String TOPIC = "spring-consumer-test";

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringKafkaConsumer.class);
        application.run(args);
    }

    // @KafkaListener 어노테이션 파라미터에 따라 메서드에 필요한 파라미터 종류 달라짐

    // 기본 리스너 형태 
    // 토픽, 그룹 id 지정하여 해당 토픽에서 레코드 가져옴
    @KafkaListener(topics = TOPIC, groupId = "test-group-0")
    public void recordListener(ConsumerRecord<String, String> record) {
        logger.info(record.toString());
    }

    // 메시지 값을 파라미터로 사용하는 리스너 
    // 레코드 생성 시 String Serializer 사용했기 때문에 String으로 받음 
    @KafkaListener(topics = TOPIC, groupId = "test-group-1")
    public void singleTopicListener(String messageValue) {
        logger.info(messageValue);
    }

    // properties 옵션으로 해당 컨슈머에게 개별 옵션 부여 
    @KafkaListener(topics = TOPIC, groupId = "test-group-2", properties =  {
        "max.poll.interval.ms:60000",
        "auto.offset.reset:earliest"
    })
    public void singleTopicWithPropertiesListener(String messageValue) {
        logger.info(messageValue);
    }

    // concurrency : 컨슈머 멀티 스레드 실행 
    // 3개 스레드로 병렬로 컨슈머가 레코드 가져옴 
    @KafkaListener(topics = TOPIC, groupId = "test-group-3", concurrency = "3")
    public void concurrentTopicListener(String messageValue) {
        logger.info(messageValue);
    }

    // 특정 토픽의 특정 파티션 값만 가져옴 (partitions)
    // 특정 오프셋부터 메시지 가져오도록도 설정 가능 (partitionOffsets)
    @KafkaListener(topicPartitions = {
        @TopicPartition(topic = TOPIC, partitions = {"0", "1"}),
        @TopicPartition(topic = TOPIC, partitionOffsets = @PartitionOffset(partition = "0", initialOffset = "3"))
        },
        groupId = "test-group-4"
    )
    public void listenSpecificPartition(ConsumerRecord<String, String> record) {
        logger.info(record.toString());
    }
}
