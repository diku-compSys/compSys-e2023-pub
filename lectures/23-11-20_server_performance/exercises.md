# Exercises for performant servers

## Exercises from Chapter 8 of Bryant and O'Hallaron on "Control Flow"

* 8.15
* 8.23

## Exercises from Chapter 12 of Bryant and O'Hallaron on "Concurrent Programming"

* 12.17
* 12.18
* 12.27
* 12.29

## Programming task
In C, create a peer that can act as a client and server at the same time. A Python example has been included which will both send and recieve messages concurrently. Your client should be able to do the same. 

Messages sent between the peers have a simple format. The only element in the header is 4 bytes giving the length of the following body. 