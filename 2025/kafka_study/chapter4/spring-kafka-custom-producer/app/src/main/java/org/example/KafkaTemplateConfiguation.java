package org.example;

import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.common.serialization.StringSerializer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.core.*;

import java.util.HashMap;
import java.util.Map;

@Configuration
public class KafkaTemplateConfiguation {
    
    // spring bean 등록 
    @Bean 
    public KafkaTemplate<String, String> customKafkaTemplate() {
        // kafka producer 설정 
        // 필수 옵션 : bootstrap-servers, key / value serializer
        Map<String, Object> props = new HashMap<>();
        props.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
        props.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        props.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG, StringSerializer.class);
        props.put(ProducerConfig.ACKS_CONFIG, "all");

        // ProducerFactory 초기화 및 생성 
        ProducerFactory<String, String> pf = new DefaultKafkaProducerFactory<>(props);

        return new KafkaTemplate<>(pf);
    }
}
