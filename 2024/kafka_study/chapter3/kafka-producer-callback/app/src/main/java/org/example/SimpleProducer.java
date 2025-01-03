package org.example;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.clients.producer.ProducerRecord;
import org.apache.kafka.clients.producer.RecordMetadata;
import org.apache.kafka.common.serialization.StringSerializer;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Properties;

public class SimpleProducer {
    // kafka logging 용
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

        long before = System.currentTimeMillis();

        // broker의 record 수신 여부 동기식 체크
        for(int i = 0; i < 100; i++) {
            String key = "syncKey" + Integer.toString(i);
            String value = "syncValue" + Integer.toString(i);

            try {
                ProducerRecord<String, String> record = new ProducerRecord<String,String>(TOPIC_NAME, key, value);
                // get() : send() 로 producer 버퍼에 저장된 레코드의 메타데이터 가져옴
                RecordMetadata metadata = producer.send(record).get();
                logger.info(metadata.toString());
            } catch (Exception e) {
                logger.error(e.getMessage(), e);
            }
        }

        // 브로커에 전송 
        producer.flush();

        long after = System.currentTimeMillis();
        long diff = after - before;
        System.out.println("동기식 처리 시간 : " + diff);

        long before2 = System.currentTimeMillis();

        // broker의 record 수신 여부 비동기 체크 
        for(int i = 0; i < 100; i++) {
            String key = "asyncKey" + Integer.toString(i);
            String value = "asyncKey" + Integer.toString(i);

            try {
                ProducerRecord<String, String> record = new ProducerRecord<String,String>(TOPIC_NAME, key, value);
                // callback 상속받은 ProducerCallback() 을 인자로 사용함으로써 
                // send() 결과 로깅을 비동기로 처리 
                producer.send(record, new ProducerCallback());
            } catch (Exception e) {
                logger.error(e.getMessage(), e);
            }
        }

        // 브로커에 전송 
        producer.flush();

        long after2 = System.currentTimeMillis();
        long diff2 = after2 - before2;
        System.out.println("비동기 처리 시간 : " + diff2);

        producer.close();
    }
}
