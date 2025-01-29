package org.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.apache.kafka.clients.consumer.Consumer;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.support.Acknowledgment;

@SpringBootApplication
public class SpringKafkaCommitConsumer {
    public static Logger logger = LoggerFactory.getLogger(SpringKafkaCommitConsumer.class);

    private static final String TOPIC = "spring-consumer-test";

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringKafkaCommitConsumer.class);
        application.run(args);
    }

    // @KafkaListener 어노테이션 파라미터에 따라 메서드에 필요한 파라미터 종류 달라짐

    // 배치 커밋 리스너
    // 지정한 Ack Mode 값이 수동 관련 (MANUAL / MANUAL_IMMEDIATE) 인 경우, 수동으로 커밋 명시해야 함
    // 또한 파라미터로 Acknowledgement 인스턴스를 받아야 한다. 
    @KafkaListener(topics = TOPIC, groupId = "test-group-000")
    public void commitListener(ConsumerRecords<String, String> records, Acknowledgment ack) {
        records.forEach(record -> logger.info(record.toString()));
        // 커밋 명시 
        ack.acknowledge();
    }

    // 배치 컨슈머 리스너 
    // 동기 / 비동기 커밋 등 컨슈머 인스턴스를 직접 이용하기 위해서는 Consumer 를 파라미터로 받으면 된다. 
    @KafkaListener(topics = TOPIC, groupId = "test-group-001")
    public void consumerCommitListener(ConsumerRecords<String, String> records, Consumer<String, String> consumer) {
        records.forEach(record -> logger.info(record.toString()));
        // 비동기로 커밋 진행 
        consumer.commitAsync();
    }
}
