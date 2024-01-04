#include "myInfo.h"

uint8_t* myMac_bytes()
{
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024];
    int success = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) { /* handle error*/ };

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { /* handle error */ }

    struct ifreq* it = ifc.ifc_req;
    const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (! (ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        }
        else { /* handle error */ }
    }

    static uint8_t mac_address[6];

    if (success){
        memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
    }
    return mac_address;
}

Mac& myMac() {
    static uint8_t* _value = myMac_bytes();
    static Mac res(_value);
    return res;
}

Ip GetMyIpAddr(char* interface)
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, interface, IFNAMSIZ -1);

    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);

    return Ip(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}


