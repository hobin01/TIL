package org.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.KafkaListener;

import java.util.List;

@SpringBootApplication
public class SpringKafkaBatchConsumer {
    public static Logger logger = LoggerFactory.getLogger(SpringKafkaBatchConsumer.class);

    private static final String TOPIC = "spring-consumer-test";

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringKafkaBatchConsumer.class);
        application.run(args);
    }

    // @KafkaListener 어노테이션 파라미터에 따라 메서드에 필요한 파라미터 종류 달라짐

    // 기본 배치 리스너 형태 
    // 토픽, 그룹 id 지정하여 해당 토픽에서 레코드 가져옴
    // ConsumerRecords를 파라미터로 받음 (배치 처리)
    @KafkaListener(topics = TOPIC, groupId = "test-group-00")
    public void batchListener(ConsumerRecords<String, String> records) {
        records.forEach(record -> logger.info(record.toString()));
    }

    // 메시지 값을 파라미터로 사용하는 리스너 
    // 레코드 생성 시 String Serializer 사용했기 때문에 String으로 받음 
    // 배치 처리로 토픽의 메시지를 여러 개 가져옴 
    @KafkaListener(topics = TOPIC, groupId = "test-group-01")
    public void batchTopicListener(List<String> list) {
        list.forEach(recordValue -> logger.info(recordValue));
    }

    // concurrency : 컨슈머 멀티 스레드 실행 
    // 3개 스레드로 병렬로 컨슈머가 레코드 가져옴 
    @KafkaListener(topics = TOPIC, groupId = "test-group-02", concurrency = "3")
    public void batchConcurrentTopicListener(ConsumerRecords<String, String> records) {
        records.forEach(record -> logger.info(record.toString()));
    }
}
