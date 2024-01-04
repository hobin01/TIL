#pragma once

#include<cstdint>
#include <arpa/inet.h>

#pragma pack(push, 1)
struct TcpHdr final{

    uint16_t src_port_;
    uint16_t dst_port_;
    uint32_t seq_num_;
    uint32_t ack_num_;
    uint8_t offset_and_reserved_;
    uint8_t flags_;
    uint16_t window_;
    uint16_t checksum_;
    uint16_t urgent_pointer_;

    uint16_t src_port() { return ntohs(src_port_); }
    uint16_t dst_port() { return ntohs(dst_port_); }
    uint32_t seq_num() { return ntohl(seq_num_); }
    uint32_t ack_num() { return ntohl(ack_num_); }
    uint8_t offset() { return (offset_and_reserved_ >> 4); }
    uint8_t reserved() { return (offset_and_reserved_ & 0x0F); }
    uint8_t flags() { return flags_; }
    uint16_t window() { return ntohs(window_); }
    uint16_t checksum() { return ntohs(checksum_); }
    uint16_t urgent_pointer() {return ntohs(urgent_pointer_); }
};

#pragma pack(pop)
