package org.example;

import org.apache.kafka.clients.consumer.ConsumerConfig;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.common.errors.WakeupException;
import org.apache.kafka.common.serialization.StringDeserializer;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.time.Duration;
import java.util.Arrays;
import java.util.Properties;

public class SimpleConsumer {
    private final static Logger logger = LoggerFactory.getLogger(SimpleConsumer.class);
    private final static String TOPIC_NAME = "test";
    private final static String BOOTSTAP_SERVERS = "localhost:9092";
    // consumer group 지정 
    private final static String GROUP_ID = "test-group";

    public static void main(String[] args) {
        // consumer에 필요한 config 내용 추가 
        Properties configs = new Properties();
        configs.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTAP_SERVERS);
        configs.put(ConsumerConfig.GROUP_ID_CONFIG, GROUP_ID);
        configs.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class.getName());
        configs.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class.getName());

        // KafkaConsumer 인스턴스 생성
        KafkaConsumer<String, String> consumer = new KafkaConsumer<>(configs);

        // test topic을 test-group에 할당
        consumer.subscribe(Arrays.asList(TOPIC_NAME));

        // 안전한 종료를 위한 shutdown hook 지정 
        // 이후 해당 프로세스 kill 하면, shutdown hook 발생 
        Runtime.getRuntime().addShutdownHook(new Thread() {
            public void run() {
                logger.info("Shutdown Hook !!!!");
                consumer.wakeup();
            }
        });

        try {
            while(true) {
                // consumer 버퍼에 1초 간격으로 데이터 polling
                ConsumerRecords<String, String> records = consumer.poll(Duration.ofSeconds(1));
                for (ConsumerRecord<String, String> record: records) {
                    logger.info("record:{}", record);
                }
            }
        } catch (WakeupException e) {
            logger.warn("Wakeup consumer");
        } finally {
            logger.warn("Consumer close");
            consumer.close();
        }
    } 
}