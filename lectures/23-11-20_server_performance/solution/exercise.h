
#pragma once
#include "csapp.h"

// container for storing ip and port
typedef struct PeerAddress {
    char ip[16];
    char port[8];
} PeerAddress_t;

// container for storing client setup args
typedef struct ClientArgs {
    PeerAddress_t address;
    char messsage[MAXLINE];
} ClientArgs_t;