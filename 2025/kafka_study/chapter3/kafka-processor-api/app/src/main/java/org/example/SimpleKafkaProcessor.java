package org.example;

import org.apache.kafka.common.serialization.Serdes;
import org.apache.kafka.streams.KafkaStreams;
import org.apache.kafka.streams.StreamsConfig;
import org.apache.kafka.streams.Topology;

import java.util.Properties;

public class SimpleKafkaProcessor {

    private static String APPLICATION_NAME = "processor-application";
    private static String BOOTSTRAP_SERVER = "localhost:9092";
    private static String STREAM_LOG = "stream_log";
    private static String STREAM_LOG_FILTER = "stream_log_filter";

    public static void main(String[] args) {
        Properties props = new Properties();
        props.put(StreamsConfig.APPLICATION_ID_CONFIG, APPLICATION_NAME);
        props.put(StreamsConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTRAP_SERVER);
        props.put(StreamsConfig.DEFAULT_KEY_SERDE_CLASS_CONFIG, Serdes.String().getClass());
        props.put(StreamsConfig.DEFAULT_VALUE_SERDE_CLASS_CONFIG, Serdes.String().getClass());

        Topology topology = new Topology(); // processor api 사용한 토폴로지 구성
        topology.addSource("Source", STREAM_LOG) // 소스 프로세서 가져옴. param[0] : 소스 프로세서 이름, param[1] : 대상 토픽
                .addProcessor("Process", 
                            () -> new FilterProcessor(),
                            "Source") // 스트림 프로세서 사용. param[0] : 스트림 프로세서 이름, param[1] : 사용자 정의 프로세서 인스턴스, param[2] : 토폴로지 상 부모 노드 
                .addSink("Sink", STREAM_LOG_FILTER, "Process"); // 데이터 저장. param[0] : 싱크 프로세서 이름, param[1] : 저장할 토픽 이름, param[2] : 토폴로지 상 부모 노드

        KafkaStreams stream = new KafkaStreams(topology, props);
        stream.start();
    }
}
