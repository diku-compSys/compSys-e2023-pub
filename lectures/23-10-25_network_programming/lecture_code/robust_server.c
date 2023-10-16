/*
 * echoserveri.c - An iterative echo server
 */

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "compsys_helpers.h"

#define	MAXLINE	 8192

int main(int argc, char **argv)
{
    int listenfd, connfd, valread;
    int opt = 1;
    struct sockaddr_in listen_address;
    int lis_addr_len = sizeof(listen_address);
    struct sockaddr_storage clientaddr;
    char *port, buf[MAXLINE];
    compsys_helper_state_t state;
    size_t n;
    port = argv[1];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // Create listening socket
    listenfd = compsys_helper_open_listenfd(port);

    while (1) {
        // Accept incoming connections
        if ((connfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&lis_addr_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        int expected_read = 5;
        compsys_helper_readinitb(&state, connfd);
        while((n = compsys_helper_readnb(&state, buf, expected_read)) != 0) { //line:netp:echo:eof
		    printf("server received %d bytes: %s\n", (int)n, buf);
        }

        // close the connected socket
        close(connfd);
    }

    // close the listening socket. In practice we won't ever reach this line
    // as the above loop is infinite, but its a good habit to get into.
    shutdown(listenfd, SHUT_RDWR);
    exit(0);
}
