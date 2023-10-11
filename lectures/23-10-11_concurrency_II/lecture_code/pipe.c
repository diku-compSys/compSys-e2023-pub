#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MSGLEN 16

int main(void) {
  char inbuf[MSGLEN];
  int p[2], i;

  if (pipe(p) < 0)
    return 1;

  if (fork() == 0) {
    // We can just provide hard coded strings, but note the length
    write(p[1], "First", MSGLEN);

    // It is better practice to provide buffers of the full length required.
    char outbuf[MSGLEN];
    memcpy(&outbuf, "Second", MSGLEN);
    write(p[1], outbuf, MSGLEN);
  } else {
    for (i = 0; i < 2; i++) {
      read(p[0], inbuf, MSGLEN);
      printf("Reading: %s\n", inbuf);
    }
  }
}