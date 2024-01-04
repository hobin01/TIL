#pragma once

#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "mac.h"
#include "ip.h"

uint8_t* myMac_bytes();
Mac& myMac();
Ip GetMyIpAddr(char* interface);
