package org.example;

import org.apache.kafka.common.config.ConfigDef;
import org.apache.kafka.common.config.ConfigException;
import org.apache.kafka.connect.connector.Task;
import org.apache.kafka.connect.errors.ConnectException;
import org.apache.kafka.connect.sink.SinkConnector;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// 토픽에서 데이터를 읽어 파일에 저장하는 커넥터 
// FileSinkConnector는 실제 커넥트에서 사용할 커넥터 이름 
public class FileSinkConnector extends SinkConnector {

    // 커넥터 설정값을 관리
    private Map<String, String> configProperties;

    @Override
    public String version() {
        // 커넥터 버전 지정
        return "1.0";
    }

    @Override
    public void start(Map<String, String> props) {
        // 커넥터 생성 시 필요한 설정 초기화 
        // FileSinkConnectorConfig 내용으로 등록 
        this.configProperties = props;
        try {
            new FileSinkConnectorConfig(props);
        } catch (ConfigException e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }

    @Override
    public Class<? extends Task> taskClass() {
        // 사용할 태스크 이름 등록 
        return FileSinkTask.class;
    }

    @Override
    public List<Map<String, String>> taskConfigs(int maxTasks) {
        // 태스크 2개 이상 시 각 태스크 별 설정값 지정
        // 여기서는 동일하게 커넥터 설정값으로 지정
        List<Map<String, String>> taskConfigs = new ArrayList<>();
        Map<String, String> taskProps = new HashMap<>();
        taskProps.putAll(configProperties);
        for (int i = 0; i < maxTasks; i++) {
            taskConfigs.add(taskProps);
        }
        return taskConfigs;
    }

    @Override
    public ConfigDef config() {
        // 커넥터에서 사용할 설정값 지정
        return FileSinkConnectorConfig.CONFIG;
    }

    @Override
    public void stop() {
        // 커넥터 종료 시 필요한 로직 작성 
    }
}