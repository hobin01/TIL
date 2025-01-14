package org.example;

import org.apache.kafka.common.config.ConfigDef;
import org.apache.kafka.common.config.ConfigException;
import org.apache.kafka.connect.connector.Task;
import org.apache.kafka.connect.errors.ConnectException;
import org.apache.kafka.connect.source.SourceConnector;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// SourceConnector 상속받아 커스텀된 FileSourceConnector 작성 
// 파일 하나를 읽어서 토픽에 전송하는 커넥터
// FileSourceConnector는 실제 커넥터에서 사용할 커넥트 이름 
public class FileSourceConnector extends SourceConnector {
    
    private final Logger logger = LoggerFactory.getLogger(FileSourceConnector.class);
    // 커넥터 설정값을 관리하는 용도 
    private Map<String, String> configProperties;

    @Override
    public String version() {
        // 커넥터 버전 지정 
        // task 버전과 일치하면서 관리하는게 좋음 
        return "1.0";
    }

    @Override 
    public void start(Map<String, String> props) {
        // 커넥터 생성 시 필요한 설정값 등록 
        // 설정은 FileSourceConnectorConfig 호출하여 등록 
        this.configProperties = props;
        try {
            new FileSourceConnectorConfig(props);
        } catch (ConfigException e) {
            throw new ConnectException(e.getMessage(), e);
        }
    }

    @Override 
    public Class<? extends Task> taskClass() {
        // 사용할 task 이름 등록 
        return FileSourceTask.class;
    }

    @Override 
    public List<Map<String, String>> taskConfigs(int maxTasks) {
        // task가 2개 이상인 경우, 각 태스크 별 설정값을 적용하기 위함 
        // 여기서는 동일하게 configProperties로 설정 
        List<Map<String, String>> taskConfigs = new ArrayList<>();
        Map<String, String> taskProps = new HashMap<>();
        
        taskProps.putAll(configProperties);
        for(int i = 0; i < maxTasks; i++) {
            taskConfigs.add(taskProps);
        }

        return taskConfigs;
    }

    @Override 
    public ConfigDef config() {
        // 커넥터에서 사용할 설정값 지정 
        return FileSourceConnectorConfig.CONFIG;
    }

    @Override 
    public void stop() {
        // 커넥터 종료 시 필요한 로직 
        // ex. jdbc 세션 종료 
    }
}
