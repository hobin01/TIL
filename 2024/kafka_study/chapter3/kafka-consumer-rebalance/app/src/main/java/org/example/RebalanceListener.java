package org.example;

import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.clients.consumer.ConsumerRebalanceListener;
import org.apache.kafka.clients.consumer.OffsetAndMetadata;
import org.apache.kafka.common.TopicPartition;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class RebalanceListener implements ConsumerRebalanceListener {
    private final static Logger logger = LoggerFactory.getLogger(RebalanceListener.class);

    private final KafkaConsumer<String, String> consumer;
    private final Map<TopicPartition, OffsetAndMetadata> currentOffsets = new HashMap<>();

    // consumer 지정 
    public RebalanceListener(KafkaConsumer<String, String> consumer) {
        this.consumer = consumer;
    }

    // 커밋 내용 추가
    public void addOffsetToTrack(String topic, int partition, long offset) {
        currentOffsets.put(
            new TopicPartition(topic, partition), 
            new OffsetAndMetadata(offset + 1, null));
    }

    // 리밸런싱 직전 수행됨
    @Override
    public void onPartitionsRevoked(Collection<TopicPartition> partitions) {
        logger.warn("Partitions are revoked : " + partitions.toString());
        // 리밸런싱 직전까지 수행되었던 처리된 내용 (레코드에 대한 오프셋) 커밋 
        consumer.commitSync(currentOffsets);
        currentOffsets.clear();
    }

    // 리밸런싱 완료 후 수행됨 
    @Override
    public void onPartitionsAssigned(Collection<TopicPartition> partitions) {
        logger.warn("Partitions are assigned : " + partitions.toString());
    }   
}
