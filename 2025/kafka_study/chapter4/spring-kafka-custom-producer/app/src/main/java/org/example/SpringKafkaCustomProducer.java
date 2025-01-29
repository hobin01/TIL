package org.example;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.core.KafkaProducerException;
import org.springframework.kafka.core.KafkaSendCallback;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.kafka.support.SendResult;
import org.springframework.util.concurrent.ListenableFuture;

@SpringBootApplication
public class SpringKafkaCustomProducer implements CommandLineRunner {

    // test용 토픽 
    private static String TOPIC_NAME = "spring-custom-test";

    // bean 등록된 템플릿 선언 
    @Autowired
    private KafkaTemplate<String, String> customKafkaTemplate;

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(SpringKafkaCustomProducer.class);
        application.run(args);
    }

    @Override
    public void run(String... args) {
        // ListenableFuture : send() 결과값에 대한 처리를 위해 사용 
        // callback 호출해 정상 적재 여부 비동기 확인 가능
        ListenableFuture<SendResult<String, String>> future = customKafkaTemplate.send(TOPIC_NAME, "custom-test");

        // onSuccess : 브로커 정상 적재 시 onSuccess 호출 
        // onFailure : 브로커 적재 실패 시 onFailure 호출 
        future.addCallback(new KafkaSendCallback<String, String>() {
            @Override
            public void onSuccess(SendResult<String, String> result) {
                System.out.println("Send Success");
                System.out.println(result);
            }

            @Override
            public void onFailure(KafkaProducerException exc) {
                System.out.println("Send fail");
                System.out.println(exc);
            }
        });
        
        // 비동기로 적재 여부 확인되기 때문에 
        // 확인을 위해 flush로 강제로 적재 실행 
        customKafkaTemplate.flush();
    }
}
