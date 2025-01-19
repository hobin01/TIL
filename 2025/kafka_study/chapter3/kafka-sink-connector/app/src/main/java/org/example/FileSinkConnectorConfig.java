package org.example;

import org.apache.kafka.common.config.AbstractConfig;
import org.apache.kafka.common.config.ConfigDef;
import org.apache.kafka.common.config.ConfigDef.Importance;
import org.apache.kafka.common.config.ConfigDef.Type;
import java.util.Map;

// 토픽의 데이터를 읽어서 파일에 저장하는 커넥터를 위한 설정 
// FileSinkConnectorConfig 라는 이름으로 커넥터에서 설정을 하면 됨
public class FileSinkConnectorConfig extends AbstractConfig {

    // 저장할 파일 경로 및 이름 지정 
    public static final String DIR_FILE_NAME = "file";
    private static final String DIR_FILE_NAME_DEFAULT_VALUE = "/Users/hobin/test2.txt";
    private static final String DIR_FILE_NAME_DOC = "저장할 디렉토리와 파일 이름";

    // 커넥터에서 사용할 옵션을 지정
    // Source Connector와는 다르게, properties를 통해 지정한 토픽에서 데이터를 가져오므로 
    // 별도 토픽을 config에 지정하지 않아도 됨. 
    public static ConfigDef CONFIG = new ConfigDef().define(DIR_FILE_NAME,
                                                    Type.STRING,
                                                    DIR_FILE_NAME_DEFAULT_VALUE,
                                                    Importance.HIGH,
                                                    DIR_FILE_NAME_DOC);

    public FileSinkConnectorConfig(Map<String, String> props) {
        super(CONFIG, props);
    }
}