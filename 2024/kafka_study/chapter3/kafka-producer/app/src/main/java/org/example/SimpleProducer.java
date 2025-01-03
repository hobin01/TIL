package org.example;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.common.serialization.StringSerializer;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Properties;

public class SimpleProducer {
    // kafka logging 요ㅇ
    private final static Logger logger = LoggerFactory.getLogger(SimpleProducer.class);
    // topic 이름 
    private final static String TOPIC_NAME = "test";
    // broker 서버 
    private final static String BOOTSTAP_SERVERS = "127.0.0.1:9092";

    public static void main(String[] args) {
        // producer 정보 입력 (key, value)
        Properties configs = new Properties();
        configs.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTAP_SERVERS);
        configs.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class.getName());
        configs.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, StringSerializer.class.getName());

        // producer 인스턴스 생성 
        KafkaProducer<String, String> producer = new KafkaProducer<>(configs);

        // 레코드에 기록될 메시지
        String messageValue = "test_message";
        // 토픽에 넣을 레코드 정보 (키 현재 없으므로 null)
        ProducerRecord<String, String> record = new ProducerRecord<>(TOPIC_NAME, messageValue);
        
        // send 호출 시, 실제 producer가 broker에 전송하는 것이 아닌, 
        // 전송할 레코드를 배치 처리  
        producer.send(record);
        // 로깅에 레코드 출력
        logger.info("{}", record);

        // flush 호출 시, 버퍼에 있는 레코드 배치를 broker에게 전송
        producer.flush();
        // producer 인스턴스 종료 
        producer.close();
    }
}
