package org.example;

import org.apache.kafka.streams.processor.ProcessorContext;
import org.apache.kafka.streams.processor.Processor;

// stream processor 생성하기 위해 Processor or Transformer 인터페이스 적용 필요
public class FilterProcessor implements Processor<String, String> {
    // ProcessorContext : 프로세서에 대한 정보를 처리 
    // stream 처리 중인 토폴로지 토픽 정보, 애플리케이션 id 조회, 프로세싱에 필요한 메서드 (schedule, forward, commit 등) 사용 
    private ProcessorContext context;

    // stream processor 생성자 
    @Override
    public void init(ProcessorContext context) {
        this.context = context;
    }

    // 실질적인 프로세싱 로직 
    // forward() : 로직 처리 후, 다음 토폴로지로 넘어가도록 함
    // 로직 처리 완료 후, commit() 으로 데이터 처리를 선언
    @Override
    public void process(String key, String value) {
        if(value.length() >= 5) {
            context.forward(key, value);
        }
        context.commit();
    }

    // 컨텍스트 종료 전 호출되는 메서드 
    // 프로세싱을 위해 사용했던 리소스 해제 등을 수행 
    @Override 
    public void close() {

    }
}
