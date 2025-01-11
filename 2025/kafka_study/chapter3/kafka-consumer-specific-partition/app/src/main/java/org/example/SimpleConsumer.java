package org.example;

import org.apache.kafka.clients.consumer.ConsumerConfig;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.common.TopicPartition;
import org.apache.kafka.common.serialization.StringDeserializer;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.time.Duration;
import java.util.Arrays;
import java.util.Collections;
import java.util.Properties;
import java.util.Set;

public class SimpleConsumer {
    private final static Logger logger = LoggerFactory.getLogger(SimpleConsumer.class);
    private final static String TOPIC_NAME = "test";
    private final static String BOOTSTAP_SERVERS = "localhost:9092";
    // consumer group 지정 
    private final static String GROUP_ID = "test-group";
    // 특정 파티션 지정 
    private final static int PARTITION_NUMBER = 0;

    public static void main(String[] args) {
        // consumer에 필요한 config 내용 추가 
        Properties configs = new Properties();
        configs.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTAP_SERVERS);
        configs.put(ConsumerConfig.GROUP_ID_CONFIG, GROUP_ID);
        configs.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class.getName());
        configs.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class.getName());

        // KafkaConsumer 인스턴스 생성
        KafkaConsumer<String, String> consumer = new KafkaConsumer<>(configs);

        // test topic의 특정 파티션에 할당 
        consumer.assign(Collections.singleton(new TopicPartition(TOPIC_NAME, PARTITION_NUMBER)));

        // 할당된 거 확인 
        Set<TopicPartition> assignedTopicPartition = consumer.assignment();
        logger.info("Assigned partitions : {}", assignedTopicPartition);

        // test 토픽에 레코드 생기면 다 갖고 오기 위해 무한 루프 
        while(true) {
            // consumer 버퍼에 1초 간격으로 데이터 polling
            ConsumerRecords<String, String> records = consumer.poll(Duration.ofSeconds(1));
            for (ConsumerRecord<String, String> record: records) {
                logger.info("record:{}", record);
            }
        }
    }
}
