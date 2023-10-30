/*
This file is intended as a collection of some networking helper functions. It 
is very heavily based upon https://csapp.cs.cmu.edu/3e/ics3/code/src/csapp.c 
and http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

Some functions have been renamed from the above implementations to emphasise 
that this is NOT standard C, and should not be relied upon to work across 
systems.
*/

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

/* Misc constants */
#define	MAXLINE	 8192  /* Max text line length */
#define MAXBUF   8192  /* Max I/O buffer size */
#define LISTENQ  1024  /* Second argument to listen() */

/* Persistent state for the robust I/O (Rio) package */
#define COMPSYS_BUFSIZE 8192
typedef struct {
    int compsys_helper_fd;                /* Descriptor for this internal buf */
    int compsys_helper_cnt;               /* Unread bytes in internal buf */
    char *compsys_helper_bufptr;          /* Next unread byte in internal buf */
    char compsys_helper_buf[COMPSYS_BUFSIZE]; /* Internal buffer */
} compsys_helper_state_t;

/* Robust read and writes */
ssize_t compsys_helper_readn(int fd, void *usrbuf, size_t n);
ssize_t compsys_helper_writen(int fd, void *usrbuf, size_t n);
void compsys_helper_readinitb(compsys_helper_state_t *rp, int fd); 
ssize_t	compsys_helper_readnb(compsys_helper_state_t *rp, void *usrbuf, size_t n);
ssize_t	compsys_helper_readlineb(compsys_helper_state_t *rp, void *usrbuf, size_t maxlen);

/* Reentrant protocol-independent client/server helpers */
int compsys_helper_open_clientfd(char *hostname, char *port);
int compsys_helper_open_listenfd(char *port);
