package org.example;

import org.apache.kafka.clients.admin.AdminClient;
import org.apache.kafka.clients.admin.DescribeConfigsResult;
import org.apache.kafka.clients.admin.ListConsumerGroupsResult;
import org.apache.kafka.clients.admin.TopicDescription;
import org.apache.kafka.clients.admin.TopicListing;
import org.apache.kafka.clients.consumer.ConsumerConfig;
import org.apache.kafka.common.Node;
import org.apache.kafka.common.config.ConfigResource;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Collections;
import java.util.Map;
import java.util.Properties;
import java.util.concurrent.ExecutionException;

public class SimpleAdmin {
    private final static Logger logger = LoggerFactory.getLogger(SimpleAdmin.class);
    private final static String BOOTSTAP_SERVERS = "localhost:9092";

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        
        // consumer에 필요한 config 내용 추가 
        Properties configs = new Properties();
        configs.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTAP_SERVERS);

        // admin client 생성 
        AdminClient admin = AdminClient.create(configs);
        
        // describeCluster() : 브로커 정보 조회 
        logger.info("==== GET BROKER INFORMATION ====");
        for(Node node : admin.describeCluster().nodes().get()) {
            logger.info("node : {}", node);
            
            ConfigResource cr = new ConfigResource(ConfigResource.Type.BROKER, node.idString());
            DescribeConfigsResult describeConfigs = admin.describeConfigs(Collections.singleton(cr));
            describeConfigs.all().get().forEach((broker, config) -> {
                config.entries().forEach(configEntry -> {
                    logger.info(configEntry.name() + " = " + configEntry.value());
                });
            });
        }

        // listTopics : 토픽 정보 조회
        logger.info("==== TOPIC LIST ====");
        for (TopicListing topicListing : admin.listTopics().listings().get()) {
            logger.info("{}", topicListing.toString());
        }

        // describeTopics : 토픽 상세 조회
        logger.info("==== 'test' TOPIC ====");
        Map<String, TopicDescription> topicInformation = admin.describeTopics(Collections.singletonList("test")).all().get();
        logger.info("{}", topicInformation);

        // listConsumerGroups : 컨슈머 그룹 조회 
        logger.info("== CONSUMER GROUPS ====");
        ListConsumerGroupsResult listConsumerGroups = admin.listConsumerGroups();
        listConsumerGroups.all().get().forEach(v -> {
            logger.info("{}", v);
        });

        admin.close();
    }
}
