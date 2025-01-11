package org.example;

import org.apache.kafka.common.serialization.Serdes;
import org.apache.kafka.streams.KafkaStreams;
import org.apache.kafka.streams.StreamsBuilder;
import org.apache.kafka.streams.StreamsConfig;
import org.apache.kafka.streams.kstream.GlobalKTable;
import org.apache.kafka.streams.kstream.KStream;

import java.util.Properties;

public class SimpleStreamApplication {
    
    private static String APPLICATION_NAME = "kstream-global-ktable-join-application";
    private static String BOOTSTRAP_SERVER = "localhost:9092";
    private static String GLOBAL_KTABLE_ADDRESS = "global_address";
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
        GlobalKTable<String, String> globalKtable = builder.globalTable(GLOBAL_KTABLE_ADDRESS);

        // join() 메서드로 join할 테이블 및 join된 메시지 지정 
        // (key, value) -> key : KStream의 key, value 중 무엇을 join 할 key로 사용할 지 결정 
        // value 선택 시, GlobalKTable의 메시지 중 key가 KStream 메시지의 value와 일치하는 값을 대상으로 join
        // 그리고 join된 key는 해당 value
        KStream<String, String> joinedStream = kstream.join(globalKtable, 
            (key, value) -> key,
            (kstreamValue, globalKtableValue) -> kstreamValue + " send to " + globalKtableValue
        );

        // to() 메서드로 메시지 보낼 토픽 지정
        joinedStream.to(JOIN_STREAM);

        // streams application 인스턴스 생성
        KafkaStreams streams = new KafkaStreams(builder.build(), props);
        // streams application 실행 
        streams.start();
    }

}
