# Exercises for DNS

## Exercises from Chapter 2 of Kurose and Ross on "Application Layer"

* P19
  * Read the dig and nslookup man pages. [This short tutorial on dig](https://www.linode.com/docs/networking/dns/use-dig-to-perform-manual-dns-queries/) might be of interest to you.
  * You can install it by installing [bind-tools](http://www.isc.org/downloads/bind/) package if you are on a UNIX machine or the client bind tools for Windows. 
* P21
* P26

## Create a C programme for DNS lookups
Use the C functions getaddrinfo (https://man7.org/linux/man-pages/man3/gai_strerror.3.html) and (https://man7.org/linux/man-pages/man3/inet_ntop.3.html) to create a program that takes a human readable address such as 'www.google.com', converts it into an appropriate IP address, and prints it to the user.


