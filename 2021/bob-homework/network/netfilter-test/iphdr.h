#pragma once

#include<cstdint>
#include <arpa/inet.h>
#include "ip.h"

#pragma pack(push, 1)
struct IpHdr final{

    uint8_t version_and_IHL_;
    uint8_t TOS_;
    uint16_t total_length_;
    uint16_t identification_;
    uint16_t flags_and_offset_;
    uint8_t TTL_;
    uint8_t protocol_;
    uint16_t checksum_;

    Ip sip_;
    Ip tip_;

    uint8_t version() { return (version_and_IHL_ >> 4); }
    uint8_t IHL() { return (version_and_IHL_ & 0x0F); }
    uint16_t total_length() { return ntohs(total_length_); }
    uint16_t identification() { return ntohs(identification_); }
    uint16_t flags() { return ntohs(flags_and_offset_ >> 13); }
    uint16_t offset() { return ntohs(flags_and_offset_ & 0x0D); }
    uint8_t TTL() { return TTL_; }
    uint8_t protocol() { return protocol_; }
    uint16_t checksum() { return ntohs(checksum_); }
    Ip sip() { return ntohl(sip_); }
    Ip tip() { return ntohl(tip_); }
};

#pragma pack(pop);
