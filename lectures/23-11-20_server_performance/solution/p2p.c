#include "csapp.h"

struct payload_package {
    char* host;
    char* port;
};

void* server(void* vargp){
    int connfd = *((int*) vargp);
    Pthread_detach(Pthread_self());
    Free(vargp);
    rio_t rio;
    char buf[MAXLINE];
    rio_readinitb(&rio,connfd);
    char* message = "this a very important message, do not share \n";
    int length = strlen(message) + 1 ;
    memcpy(buf,&length, 4 );
    memcpy(buf+4, message, length);
    Rio_writen(connfd,buf, 4 +length);
    Close(connfd);
    return 0;
}

void* client(void* vargp) {
    struct payload_package p = *(struct payload_package *) vargp;
    rio_t rio;
    char buf[MAXLINE];

    while (1){
        
        int clientfd = Open_clientfd(p.host, p.port);
        if (clientfd) {
            Rio_readinitb(&rio, clientfd);
            Rio_readnb(&rio, buf, 4);
            int length = *(int*)buf;
            Rio_readnb(&rio, buf, length);
            printf("message is %s \n", buf);
        } else {
            printf("connection went wrong trying again in 5 seconds \n");
        }
            Sleep(5);
        

    }
    exit(0);
}

int main (int argc, char** argv) {
    int listenfd, *connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    char* c_host = argv[2];
    char* c_port = argv[3];


    if (argc != 5) {
        exit(1);
    }

    //// *****************
    pthread_t cid;
    //pthread_t sid;
    struct payload_package p;
    p.host = c_host;
    p.port = c_port;


    //Pthread_create(&sid, NULL, server )
    if(strncmp("-p", argv[4], 2) != 0 ) {
    Pthread_create(&cid, NULL, client, &p);
    }


    ///********************
    

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen=sizeof(struct sockaddr_storage);
        connfdp = Malloc(sizeof(int)); //line:conc:echoservert:beginmalloc
        *connfdp = Accept(listenfd, (SA *) &clientaddr, &clientlen); //line:conc:echoservert:endmalloc
        Pthread_create(&tid, NULL, server, connfdp);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s) via thread %lu\n",
           client_hostname, client_port, (long) tid);
    }
    return 0;
}
