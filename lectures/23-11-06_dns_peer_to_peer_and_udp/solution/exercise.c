#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "./exercise.h"

// adapted from example in 
// https://man7.org/linux/man-pages/man3/gai_strerror.3.html
int main(int argc, char **argv)
{
    struct addrinfo hints, *result, *res;
    char addrstr[100];
    int status;
    void *ptr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;      /* IPv4 */
    hints.ai_socktype = SOCK_STREAM;/* Any socket type */
    hints.ai_protocol = 0;          /* Any protocol */
           
    status = getaddrinfo("www.theguardian.com", NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    res = result;

    while (res)
    {
        ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
        inet_ntop (res->ai_family, ptr, addrstr, 100);
        printf ("IPv4 address: %s\n", addrstr);
        res = res->ai_next;
    }

    exit(EXIT_SUCCESS);
}
