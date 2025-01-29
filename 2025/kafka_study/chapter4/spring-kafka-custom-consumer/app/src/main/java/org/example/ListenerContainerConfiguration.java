package org.example;

import org.apache.kafka.clients.consumer.Consumer;
import org.apache.kafka.clients.consumer.ConsumerConfig;
import org.apache.kafka.common.serialization.StringDeserializer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.kafka.config.ConcurrentKafkaListenerContainerFactory;
import org.springframework.kafka.config.KafkaListenerContainerFactory;
import org.springframework.kafka.core.DefaultKafkaConsumerFactory;
import org.springframework.kafka.listener.*;
import org.apache.kafka.common.TopicPartition;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

@Configuration
public class ListenerContainerConfiguration {

    // spring bean 생성 
    @Bean
    public KafkaListenerContainerFactory<ConcurrentMessageListenerContainer<String, String>> customContainerFactory() {

        // 리스너 설정값 지정 
        Map<String, Object> props = new HashMap<>();
        props.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
        props.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class);
        props.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, StringDeserializer.class);

        // kafka consumer factory 생성 
        DefaultKafkaConsumerFactory cf = new DefaultKafkaConsumerFactory<>(props);

        // 리스너 컨테이너 생성 위해 선언 
        // 2개 이상의 컨슈머 리스너 사용 시, concurrency 값 스레드에 맞게 설정. 1로 설정 시 1개 스레드로 실행 
        ConcurrentKafkaListenerContainerFactory<String, String> factory = new ConcurrentKafkaListenerContainerFactory<>();
        
        // 리밸런스 리스너 선언 위해 setConsumerRebalanceListener 메서드 호출 
        factory.getContainerProperties().setConsumerRebalanceListener(new ConsumerAwareRebalanceListener() {
            @Override
            public void onPartitionsRevokedBeforeCommit(Consumer<?, ?> consumer, Collection<TopicPartition> partitions) {
                // 커밋 되기 전 리밸런스 발생했을 때 로직 작성
            }

            @Override
            public void onPartitionsRevokedAfterCommit(Consumer<?, ?> consumer, Collection<TopicPartition> partitions) {
                // 커밋 일어난 후 리밸런스 발생했을 때 로직 작성 
            }

            @Override
            public void onPartitionsAssigned(Collection<TopicPartition> partitions) {
                // 컨슈머가 새로운 파티션을 할당받을 때 로직 작성
            }

            @Override
            public void onPartitionsLost(Collection<TopicPartition> partitions) {
                // 컨슈머가 파티션 잃을 때 (컨슈머 종료, 네트워크 에러 등) 로직 작성
            }
        });
        
        // 레코드 리스너 사용 명시를 위해 false 선언. 배치 리스너 사용 시 true 사용 
        factory.setBatchListener(false);
        // AckMode 값 설정 
        factory.getContainerProperties().setAckMode(ContainerProperties.AckMode.RECORD);
        // 컨슈머 설정값을 갖고 있는 팩토리 인스턴스를 ConcurrentKafkaListenerContainerFactory 팩토리에 등록 
        factory.setConsumerFactory(cf);

        return factory;
    }
}