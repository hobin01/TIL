package org.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.KafkaListener;

@SpringBootApplication
public class SpringConsumerApplication {
    public static Logger logger = LoggerFactory.getLogger(SpringConsumerApplication.class);

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringConsumerApplication.class);
        application.run(args);
    }

    // ListenerContainerConfiguration.java에서 bean 등록한 객체 containerFactory로 선언하여 
    // 커스텀 컨슈머 리스너를 적용 
    @KafkaListener(topics = "spring-consumer-test",
            groupId = "test-group-002",
            containerFactory = "customContainerFactory")
    public void customListener(String data) {
        logger.info(data);
    }
}