package org.example;

import org.apache.kafka.common.serialization.Serdes;
import org.apache.kafka.streams.KafkaStreams;
import org.apache.kafka.streams.StreamsBuilder;
import org.apache.kafka.streams.StreamsConfig;
import org.apache.kafka.streams.kstream.KStream;

import java.util.Properties;

public class SimpleStreamApplication {
    
    private static String APPLICATION_NAME = "streams-filter-application";
    private static String BOOTSTRAP_SERVER = "localhost:9092";
    private static String STREAM_LOG = "stream_log";
    private static String STREAM_LOG_COPY = "stream_log_filter";

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
        // stream() 메서드로 KStream 객체 생성 (소스 프로세서)
        KStream<String, String> stream = builder.stream(STREAM_LOG);

        // 메시지 value 길이 5 이상인 것만 필터링 (스트림 프로세서)
        KStream<String, String> filteredStream = stream.filter((k, v) -> {
            return v.length() >= 5;
        });

        // to() 메서드로 메시지 보낼 토픽 지정 (싱크 프로세서)
        // filteredStream = stream.filter(...).to(...) 로 간소화 가능
        filteredStream.to(STREAM_LOG_COPY);

        // streams application 인스턴스 생성
        KafkaStreams streamApplication = new KafkaStreams(builder.build(), props);
        // streams application 실행 
        streamApplication.start();
    }

}
