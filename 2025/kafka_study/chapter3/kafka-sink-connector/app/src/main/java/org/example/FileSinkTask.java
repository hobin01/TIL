package org.example;

import org.apache.kafka.clients.consumer.OffsetAndMetadata;
import org.apache.kafka.common.TopicPartition;
import org.apache.kafka.connect.errors.ConnectException;
import org.apache.kafka.connect.sink.SinkRecord;
import org.apache.kafka.connect.sink.SinkTask;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collection;
import java.util.Map;

// 실제 sink 관련 로직 수행할 태스크 
public class FileSinkTask extends SinkTask {
    // 커넥터 설정, 저장할 파일, 파일에 쓰기 위한 writer 스트림
    private FileSinkConnectorConfig config;
    private File file;
    private FileWriter fileWriter;

    @Override
    public String version() {
        // 버전 지정 
        return "1.0";
    }

    @Override
    public void start(Map<String, String> props) {
        // 태스크 초기 설정 
        // FileSinkConnectorConfig에서 설정한 값으로 지정
        try {
            config = new FileSinkConnectorConfig(props);
            file = new File(config.getString(config.DIR_FILE_NAME));
            fileWriter = new FileWriter(file, true);
        } catch (Exception e) {
            throw new ConnectException(e.getMessage(), e);
        }

    }

    @Override
    public void put(Collection<SinkRecord> records) {
        // 토픽에서 데이터 가져오는 로직 
        // SinkRecord : 토픽의 하나의 레코드에 대한 정보를 의미 
        try {
            for (SinkRecord record : records) {
                fileWriter.write(record.value().toString() + "\n");
            }
        } catch (IOException e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }

    @Override
    public void flush(Map<TopicPartition, OffsetAndMetadata> offsets) {
        // put으로 가져온 데이터를 실질적으로 반영하는 로직 (commit 역할)
        try {
            fileWriter.flush();
        } catch (IOException e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }

    @Override
    public void stop() {
        // 태스크 종료 시 수행할 로직 
        // 여기서는 writer를 종료
        try {
            fileWriter.close();
        } catch (IOException e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }
}