/*
 * echoserveri.c - An iterative echo server
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>


#define	MAXLINE	 8192

typedef struct {
  int connfd;
} targ_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char var[MAXLINE];
int set = 0;

void* echo(void* arg)
{
    int* connfd = (int*)arg; //((targ_t*)arg)->connfd;
    char buf[MAXLINE];
    int valread;

    // Keep looping until we encounter an EOF char, e.g. the connection was 
    // closed
    while((valread = read(*connfd, buf, MAXLINE)) != 0) {
        printf("Recieved %d bytes: %s\n", valread, buf);
        
// TASK 2
        char input1[MAXLINE];
        char input2[MAXLINE]; 
        char* retval;
        sscanf(buf, "%s %s\n", input1, input2);
        if (strcmp(input1, "PUT") == 0) {
          pthread_mutex_lock(&mutex);
          if (set) {
            printf("Client requested to store a variable, but it is already set.\n");
            retval = "VARIABLE FILLED\n"; 
            strcpy(buf, retval);
          }
          else {
            strcpy(var, input2);
            set = 1;
            printf("Internal variable set to: %s\n", var);
            retval = "OK\n";
            strcpy(buf, retval);
            pthread_cond_broadcast(&cond);
          }
          pthread_mutex_unlock(&mutex);
          write(*connfd, buf, strlen(buf));
        }
        
        else if (strcmp(buf, "GET\n") == 0) { 
          printf("Client requested stored variable, but it is not set - blocking.\n");
          pthread_mutex_lock(&mutex);
          while (!set) {
            pthread_cond_wait(&cond, &mutex);
          }
          printf("Retrieving stored variable.\n");
          write(*connfd, var, strlen(var));
          pthread_mutex_unlock(&mutex);
        }
//TASK 1
        else {
          printf("%s", buf);
          if (strcmp("ping\n", buf) == 0) {
            buf[1] = 'o'; 
          } else {
            retval = "BAD REQUEST\n";
            strcpy(buf, retval);     
          }
          write(*connfd, buf, strlen(buf));       
        }
        memset(buf, 0, MAXLINE);
    }
    close(*connfd);
    free(connfd);
// TASK 1

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

    // Setup socket address and flags
    if (setsockopt(listenfd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
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
    pthread_t tids[16];
    int tids_index = 0;
    while (1) {
        // Accept incoming connections
        if ((connfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&lis_addr_len)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int* pid_connfd = malloc(sizeof(int));
        *pid_connfd = connfd;
        pthread_create(&tids[tids_index++], NULL, echo, (void*)pid_connfd);

    }

    //Unreachable code
    for (int i = 0; i < tids_index; i++) {
      pthread_join(tids[i], NULL);
    }

    // close the listening socket. In practice we won't ever reach this line
    // as the above loop is infinite, but its a good habit to get into.
    shutdown(listenfd, SHUT_RDWR);
    exit(0);
}
