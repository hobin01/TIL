package org.example;

import org.apache.kafka.common.config.AbstractConfig;
import org.apache.kafka.common.config.ConfigDef;
import org.apache.kafka.common.config.ConfigDef.Importance;
import org.apache.kafka.common.config.ConfigDef.Type;

import java.util.Map;

// 파일을 읽어서 토픽에 메시지 보낼 커넥터를 위한 설정 
// FileSourceConnectorConfig 라는 이름으로 실제 커넥터에서 설정을 하면 됨
public class FileSourceConnectorConfig extends AbstractConfig {
    
    // 읽을 파일 경로 및 이름을 지정
    // 다른 class에서는 file 이라는 값으로 해당 파일을 읽음 
    public static final String DIR_FILE_NAME = "file";
    private static final String DIR_FILE_NAME_DEFAULT_VALUE = "/Users/hobin/test.txt";
    private static final String DIR_FILE_NAME_DOC = "읽을 파일 경로 및 이름";

    // 메시지를 보낼 토픽을 지정 
    // 다른 class에서는 topic 이라는 값으로 해당 토픽에 메시지를 보냄
    public static final String TOPIC_NAME = "topic";
    private static final String TOPIC_DEFAULT_VALUE = "custom-connector-test";
    private static final String TOPIC_DOC = "보낼 토픽";

    // ConfigDef를 이용해서 파일, 토픽을 지정한다. 
    public static ConfigDef CONFIG = new ConfigDef().define(
            DIR_FILE_NAME, Type.STRING, DIR_FILE_NAME_DEFAULT_VALUE, Importance.HIGH, DIR_FILE_NAME_DOC
        ).define(
            TOPIC_NAME, Type.STRING, TOPIC_DEFAULT_VALUE, Importance.HIGH, TOPIC_DOC
        );

    // AbstractConfig 이용해서 작성한 config를 적용한다.  
    public FileSourceConnectorConfig(Map<String, String> props) {
        super(CONFIG, props);
    }
}
