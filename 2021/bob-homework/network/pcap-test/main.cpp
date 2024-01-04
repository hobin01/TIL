#include <pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <libnet.h>

void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

struct Param{
    char* device = NULL;
}param;

bool parse(Param* param, int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return false;
    }
    param->device = argv[1];
    return true;
}

void print_line(char name[]){
    printf("===========%s============\n", name);
}

void print_eth_MAC(struct libnet_ethernet_hdr *eth){
    char name[] = "Ethernet";
    print_line(name);

    printf("src MAC : ");
    for(int i = 0; i < ETHER_ADDR_LEN ; i++){
        printf("%02x : ", eth->ether_shost[i]);
    }
    printf("\n");
    printf("dst MAC : ");
    for(int i = 0; i < ETHER_ADDR_LEN; i++){
        printf("%02x : ", eth->ether_dhost[i]);
    }
    printf("\n");
}

void change_to_bytes_and_print_ip(u_int32_t addr){
    uint8_t bytes[4];
    bytes[0] = (addr >> 24) & 0xFF;
    bytes[1] = (addr >> 16) & 0xFF;
    bytes[2] = (addr >> 8) & 0xFF;
    bytes[3] = addr & 0xFF;

    for(int i = 0; i < 4; i++){
        printf("%3d.", bytes[i]);
    }
    printf("\n");
}

void print_IP_ip(struct libnet_ipv4_hdr *ip){
    char name[] = "IP";
    print_line(name);

    // s_addr : big endian
    u_int32_t src = ntohl(ip->ip_src.s_addr);
    u_int32_t dst = ntohl(ip->ip_dst.s_addr);

    printf("src ip : ");
    change_to_bytes_and_print_ip(src);

    printf("dst ip : ");
    change_to_bytes_and_print_ip(dst);
}

void print_TCP_port(struct libnet_tcp_hdr *tcp){
    char name[] = "TCP";
    print_line(name);

    printf("src port : %d\n", ntohs(tcp->th_sport));
    printf("dst port : %d\n", ntohs(tcp->th_dport));
}

void print_data_8bytes(const u_char* packet, uint8_t offset)
{
    char name[] = "DATA";
    print_line(name);

    for(uint8_t i = 0; i < 8; i++){
        printf("%2x | ", *(packet + offset + i));
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    if (!parse(&param, argc, argv))
            return -1;

    char ebuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(param.device, BUFSIZ, true, 1000, ebuf);

    if (pcap == NULL) {
        fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.device, ebuf);
        return -1;
    }

    int result = 0;

    while(true){
        struct pcap_pkthdr* header;
        const u_char* packet;
        result = pcap_next_ex(pcap, &header, &packet);

        if(result == 0)
            continue;

        if(result < 0){
            printf("pcap_next_ex return %d(%s)\n", result, pcap_geterr(pcap));
            break;
        }

        struct libnet_ethernet_hdr* eth = (struct libnet_ethernet_hdr*)packet;
        struct libnet_ipv4_hdr* ip = (struct libnet_ipv4_hdr*)(packet + 14); // ethernet 14bytes
        struct libnet_tcp_hdr* tcp = (struct libnet_tcp_hdr*)(packet + 14 + ip->ip_hl * 4);
        // ethernet 14bytes + ip_hl (header length, the number of 4bytes)

        if(ntohs(eth->ether_type) != 0x0800) // ether_type : 0x0800 = ip
            continue;
        if((ip->ip_p) != 6) // ip_p (protocol) : TCP = 6
            continue;
        if((packet + 14 + ip->ip_hl * 4 + tcp->th_off * 4) == NULL) // No data
            continue;

        print_eth_MAC(eth);
        print_IP_ip(ip);
        print_TCP_port(tcp);

        uint8_t d_offset = 14 + ip->ip_hl * 4 + tcp->th_off * 4; // packet to data start offset
        print_data_8bytes(packet, d_offset);

    }

    pcap_close(pcap);
}

