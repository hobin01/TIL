package org.example;

import org.apache.kafka.connect.data.Schema;
import org.apache.kafka.connect.errors.ConnectException;
import org.apache.kafka.connect.source.SourceRecord;
import org.apache.kafka.connect.source.SourceTask;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

// 실제 로직을 수행하는 task
public class FileSourceTask extends SourceTask {
    private Logger logger = LoggerFactory.getLogger(FileSourceTask.class);

    // 읽는 파일 이름, 읽은 지점을 오프셋 스토리지에 저장하기 위함
    public final String FILENAME_FIELD = "filename";
    public final String POSITION_FIELD = "position";

    // filename을 키, 실제 파일 이름을 value로 사용한다. 
    private Map<String, String> fileNamePartition;
    // 커넥터가 읽은 지점인 오프셋 저장하기 위함 
    private Map<String, Object> offset;
    private String topic;
    private String file;
    private long position = -1;


    @Override
    public String version() {
        // task 버전을 명시, connector 버전과 동일하게 관리하면 좋음 
        return "1.0";
    }

    @Override
    public void start(Map<String, String> props) {
        try {
            // task에 대한 초기 설정 
            // connector config에서 설정한 값을 가져온다. 
            FileSourceConnectorConfig config = new FileSourceConnectorConfig(props);
            topic = config.getString(FileSourceConnectorConfig.TOPIC_NAME);
            file = config.getString(FileSourceConnectorConfig.DIR_FILE_NAME);
            // 읽을 파일 및 오프셋을 설정한다. 
            fileNamePartition = Collections.singletonMap(FILENAME_FIELD, file);
            offset = context.offsetStorageReader().offset(fileNamePartition);


            if (offset != null) {
                // 현재까지 처리된 오프셋 정보를 가져온다. 
                Object lastReadFileOffset = offset.get(POSITION_FIELD);
                if (lastReadFileOffset != null) {
                    position = (Long) lastReadFileOffset;
                }
            } else {
                // 처리된 게 없으면 처음부터 진행 
                position = 0;
            }

        } catch (Exception e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }

    @Override
    public List<SourceRecord> poll() {
        // 파일을 지속적으로 읽기 위한 실질적인 task 
        List<SourceRecord> results = new ArrayList<>();
        try {
            // 1초 단위로 파일 체크 
            Thread.sleep(1000);

            // position line 이후부터 읽기 
            List<String> lines = getLines(position);

            if (lines.size() > 0) {
                // 처리할 거 있을 시, 
                // SourceRecord 타입으로 읽은 내용 처리 
                lines.forEach(line -> {
                    Map<String, Long> sourceOffset = Collections.singletonMap(POSITION_FIELD, ++position);
                    SourceRecord sourceRecord = new SourceRecord(fileNamePartition, sourceOffset, topic, Schema.STRING_SCHEMA, line);
                    results.add(sourceRecord);
                });
            }
            // 읽은 내용 polling
            return results;
        } catch (Exception e) {
            logger.error(e.getMessage(), e);
            throw new ConnectException(e.getMessage(), e);
        }
    }

    private List<String> getLines(long readLine) throws Exception {
        // 파일에서 해당 라인 이후부터 읽음 
        BufferedReader reader = Files.newBufferedReader(Paths.get(file));
        return reader.lines().skip(readLine).collect(Collectors.toList());
    }

    @Override
    public void stop() {
        // task 종료할 때 처리할 로직 
    }
}
