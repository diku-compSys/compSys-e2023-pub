/*
 * echoclient.c - An echo client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> 

#include "compsys_helpers.h"

#define	MAXLINE	 8192

int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port;
    struct sockaddr_in serv_addr;
    compsys_helper_state_t state;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    // Create our socket and connect    
    clientfd = compsys_helper_open_clientfd(host, port);

    printf("Starting to send\n");

    // Write the buffer to the socket
    compsys_helper_writen(clientfd, "msg1\0", 5);
    sleep(1);
    compsys_helper_writen(clientfd, "ms", 2);
    sleep(1);
    compsys_helper_writen(clientfd, "g2\0", 3);
    sleep(1);
    compsys_helper_writen(clientfd, "msg3\0", 5);
    sleep(1);

    printf("Sent all delayed messages\n");

    compsys_helper_writen(clientfd, "msg1\0", 5);
    compsys_helper_writen(clientfd, "msg\0", 4);
    compsys_helper_writen(clientfd, "msg3\0", 5);

    printf("Sent all 'instant' messages\n");

    // Make sure to close our socket. In practice we won't ever reach this line
    // as the above loop is infinite, but its a good habit to get into.
    close(clientfd);
    exit(0);
}
