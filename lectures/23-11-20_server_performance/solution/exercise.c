#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "./exercise.h"


void* client_thread(void* thread_args)
{
    struct ClientArgs *client_args = thread_args;
    rio_t rio;
    uint32_t loop_counter = 0;

    while(loop_counter<10)
    {
        printf("C - [%d] Connectiong to %s:%s\n", loop_counter, client_args->address.ip, client_args->address.port);
        int peer_socket = Open_clientfd(client_args->address.ip, client_args->address.port);
        Rio_readinitb(&rio, peer_socket);

        char message[strlen(client_args->messsage) + 4];
        uint32_t networked_length = htonl(strlen((client_args->messsage)));
        memcpy(message, &networked_length, 4);
        memcpy(message+4, client_args->messsage, strlen((client_args->messsage)));

        Rio_writen(peer_socket, message, strlen(client_args->messsage)+4);

        sleep(1);
        loop_counter++;
    }
}


void handle_server_request(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    Rio_readnb(&rio, buf, 4);
    
    uint32_t request_length = ntohl(*(uint32_t*)&buf);

    // Read the rest of the message
    Rio_readnb(&rio, buf, request_length);
    char message[request_length];
    memcpy(message, buf, request_length);
    printf("S - Recieved message: %s\n", message);
}


void* server_thread(void* thread_args)
{
    struct PeerAddress *my_address = thread_args;
    int listenfd;
    int connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    // Start listening
    listenfd = Open_listenfd(my_address->port);
    printf("Starting to listen on %s:%s\n", my_address->ip, my_address->port);

    while (1) {
        // Any incoming calls are handled in a new server thread
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        printf("we get after accpet \n");
        if (Fork() == 0) {
            Close(listenfd);
            pid_t childpid = getpid();
            handle_server_request(connfd);
            Close(connfd);
            exit(0);
        }
        Close(connfd);
    }

    // You should never see this printed
    printf("Server thread done\n");
}


int main(int argc, char **argv)
{   
    char* my_ip = argv[1];
    char* my_port = argv[2];
    struct PeerAddress my_address;
    memcpy(my_address.ip, my_ip, 16);
    memcpy(my_address.port, my_port, 8);

    pthread_t client_thread_id;
    if (argc > 3) {
      char* peer_ip = argv[3];
      char* peer_port = argv[4];

      struct PeerAddress peer_address;
      memcpy(peer_address.ip, peer_ip, 16);
      memcpy(peer_address.port, peer_port, 8);
      char message[MAXLINE];
      sprintf(message, "Hello from %s:%s\0", my_address.ip, my_address.port);
      printf("%s\n", message);
      struct ClientArgs client_args;
      client_args.address = peer_address;
      memcpy(client_args.messsage, message, MAXLINE);
      pthread_create(&client_thread_id, NULL, client_thread, &client_args);
    }
    // Setup the client and server threads 
    pthread_t server_thread_id;
    pthread_create(&server_thread_id, NULL, server_thread, &my_address);

    // Start the threads. Note that the client is only started if a peer is 
    // provided in the config. If none is we will assume this peer is the first
    // on the network and so cannot act as a client.
    if (argc > 3) {
      pthread_join(client_thread_id, NULL);
    }
    pthread_join(server_thread_id, NULL);
    printf("we get here \n");

    exit(EXIT_SUCCESS);

}
