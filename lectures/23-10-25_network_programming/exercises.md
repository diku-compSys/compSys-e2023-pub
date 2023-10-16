# Exercises for Network Programming

## An echoing server
Within the lecture_code directory you should find a very simple server and client. You can start a server on port 12345 with:

    ./echoserver 12345

You can then start a client to connect to that server with:

    ./echoclient 0.0.0.0 12345

Note that both will run forver, with the client waiting for you to type in some text, which will be sent to the server.

### Ping/pong
Modify the server so that if it recieves a `ping` message, it replies with a `pong`. In all other cases the server returns `BAD REQUEST`.

### Distributed variable
The server accepts two different kinds of messages.

* `PUT [SOME STRING]` that stores a string in the internal storage of the server. Note that the first space is a separator and thus part of the protocol syntax.
* `GET` that returns the string that is stored.

When the server receives a `PUT` it saves the string to an internal variable and returns `OK`. The following `PUT` messages will not update the variable, but return `VARIABLE FILLED`.

When the server receives a `GET` it returns the stored variable. All `GET`s should be blocking, until the server has received the first `PUT`. Thus, clients sending a `GET` before another client send a `PUT` should block and wait until the server receives the first `PUT` and responds to all waiting clients.

### Sending messages of an unknown length
The echoclient and echoserver both only work when sending a message of fixed length MAXLINE. This might be incredibly wasteful if we have to send and read 8192 bytes every time, even if we're only actually sending a short message like 'First'. For this reason we don't do this in the real world, but instead send headers that describe how long the message is going to be.

Rework the echoclient and echoserver so that they can send a header of a fixed length, and then a message of the length stated in the header. For instance if sending the message 'First' you might send something of the form '5First'. The server should then read just the header to find out how much else is to be read, and then should read that many bytes. You will have to decide on a sensible length for your header.