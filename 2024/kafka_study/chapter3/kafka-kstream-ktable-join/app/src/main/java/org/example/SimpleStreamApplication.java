package org.example;

import org.apache.kafka.common.serialization.Serdes;
import org.apache.kafka.streams.KafkaStreams;
import org.apache.kafka.streams.StreamsBuilder;
import org.apache.kafka.streams.StreamsConfig;
import org.apache.kafka.streams.kstream.KStream;
import org.apache.kafka.streams.kstream.KTable;

import java.util.Properties;

public class SimpleStreamApplication {
    
    private static String APPLICATION_NAME = "kstream-ktable-join-application";
    private static String BOOTSTRAP_SERVER = "localhost:9092";
    private static String KTABLE_ADDRESS = "address";
    private static String KSTREAM_ITEM = "item";
    private static String JOIN_STREAM = "join_stream";

    public static void main(String[] args) {
        Properties props = new Properties();

        // streams application id 등록
        props.put(StreamsConfig.APPLICATION_ID_CONFIG, APPLICATION_NAME);
        // streams application과 연동할 클러스터 서버
        props.put(StreamsConfig.BOOTSTRAP_SERVERS_CONFIG, BOOTSTRAP_SERVER);
        // streams application에서 사용할 메시지 key, value 직렬화 종류
        props.put(StreamsConfig.DEFAULT_KEY_SERDE_CLASS_CONFIG, Serdes.String().getClass());
        props.put(StreamsConfig.DEFAULT_VALUE_SERDE_CLASS_CONFIG, Serdes.String().getClass());

        // streams application에 사용할 topology 정의
        StreamsBuilder builder = new StreamsBuilder();
        // stream() 메서드로 KStream 객체 생성
        // table() 메서드로 KTable 객체 생성
        KStream<String, String> kstream = builder.stream(KSTREAM_ITEM);
        KTable<String, String> ktable = builder.table(KTABLE_ADDRESS);

        // join() 메서드로 join할 테이블 및 join된 메시지 지정 (key 기준 join)
        KStream<String, String> joinedStream = kstream.join(ktable, (kstream_value, ktable_value) -> kstream_value + " send to " + ktable_value);

        // to() 메서드로 메시지 보낼 토픽 지정
        joinedStream.to(JOIN_STREAM);

        // streams application 인스턴스 생성
        KafkaStreams streams = new KafkaStreams(builder.build(), props);
        // streams application 실행 
        streams.start();
    }

}
