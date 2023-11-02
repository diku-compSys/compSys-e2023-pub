/*
 * echoserveri.c - An iterative echo server
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define	MAXLINE	 8192

void echo(int connfd)
{
    char buf[MAXLINE];
    int valread;

    // Keep looping until we encounter an EOF char, e.g. the connection was 
    // closed
    while((valread = read(connfd, buf, MAXLINE)) != 0) {
        printf("Recieved %d bytes: %s\n", valread, buf);
        write(connfd, buf, valread);
    }
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    int opt = 1;
    struct sockaddr_in listen_address;
    int lis_addr_len = sizeof(listen_address);
    struct sockaddr_storage clientaddr;
    char *port;
    port = argv[1];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    // Create listening socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //// Setup socket address and flags
    //if (setsockopt(listenfd, SOL_SOCKET,
    //               SO_REUSEADDR | SO_REUSEPORT, &opt,
    //               sizeof(opt))) {
    //    perror("setsockopt");
    //    exit(EXIT_FAILURE);
    //}
    listen_address.sin_family = AF_INET;
    listen_address.sin_addr.s_addr = INADDR_ANY;
    listen_address.sin_port = htons(atoi(port));

    // Bind socket to the listening port
    if (bind(listenfd, (struct sockaddr*)&listen_address, lis_addr_len) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(listenfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept incoming connections
        if ((connfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&lis_addr_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        echo(connfd);

        // close the connected socket
        close(connfd);
    }

    // close the listening socket. In practice we won't ever reach this line
    // as the above loop is infinite, but its a good habit to get into.
    shutdown(listenfd, SHUT_RDWR);
    exit(0);
}
