package org.example;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.core.KafkaTemplate;

@SpringBootApplication
public class SpringKafkaProducer implements CommandLineRunner {

    // test용 토픽 
    private static String TOPIC_NAME = "spring-test";

    // spring에서 제공하는 KafkaTemplate 사용 
    @Autowired
    private KafkaTemplate<Integer, String> template;

    public static void main(String[] args) {
        // spring 실행 
        SpringApplication application = new SpringApplication(SpringKafkaProducer.class);
        application.run(args);
    }

    // CommandLineRunner의 run() override
    @Override
    public void run(String... args) {
        for(int i = 0; i < 10; i++) {
            template.send(TOPIC_NAME, "test" + i);
        }
        System.exit(0);
    }
}
