/*
 * echoclient.c - An echo client
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> 

#define	MAXLINE	 8192

int main(int argc, char **argv) 
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    struct sockaddr_in serv_addr;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    // Create our socket 
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    // Setup the address we will connect to and convert IPv4 and IPv6 addresses
    // from text to binary form
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port));
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    // Make a connection to an already running socket
    if ((connect(clientfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Start the user interaction
    printf("This program will attempt to send a string to a server. Type one "
           "here and hit enter to send: ");
    // Get some text from stdin and put it in a buffer
    while (fgets(buf, MAXLINE, stdin) != NULL) {

        // Write the buffer to the socket
        write(clientfd, buf, strlen(buf));
        // Read from the buffer 
        read(clientfd, buf, MAXLINE);
        printf("Recieved reply: ");
        // Send the reply to stdout
        fputs(buf, stdout);
        printf("Enter another string: ");
    }

    // Make sure to close our socket. In practice we won't ever reach this line
    // as the above loop is infinite, but its a good habit to get into.
    close(clientfd);
    exit(0);
}
