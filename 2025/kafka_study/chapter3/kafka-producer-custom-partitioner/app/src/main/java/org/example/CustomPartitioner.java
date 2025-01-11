package org.example;

import org.apache.kafka.clients.producer.Partitioner;
import org.apache.kafka.common.Cluster;
import org.apache.kafka.common.InvalidRecordException;
import org.apache.kafka.common.PartitionInfo;
import org.apache.kafka.common.utils.Utils;

import java.util.List;
import java.util.Map;

// Partitioner interface 상속받은 CustomPartitioner 
// 특정 키 갖는 레코드를 특정 파티션에 넣기 위함 
// 파티션 개수 늘어나면, 키가 동일하더라도 늘어나기 전 후 동일 파티션에 레코드 들어갈 지 모르기 때문 

// 필수 구현 메서드 : partition, configure, close 

public class CustomPartitioner implements Partitioner {
    @Override
    public int partition(String topic, Object key, byte[] keyBytes, 
                        Object value, byte[] valueBytes, Cluster cluster) {
        
        // key 값 없는 경우, 에러 발생 
        if(keyBytes == null) {
            throw new InvalidRecordException("Need message key!!!");
        }

        // key == "Zero" 인 경우 0번 파티션으로 고정 
        if(((String)key).equals("Zero")) {
            return 0;
        }

        // 토픽에 대한 파티션 리스트 
        List<PartitionInfo> partitions = cluster.partitionsForTopic(topic);
        // 파티션 전체 개수 
        int numPartitions = partitions.size();
        // 키 해시 (murmur2) 값에 따라 파티션 할당 
        return Utils.toPositive(Utils.murmur2(keyBytes)) % numPartitions;
    }

    @Override
    public void configure(Map<String, ?> configs) {}

    @Override 
    public void close() {}
}
