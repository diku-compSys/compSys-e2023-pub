# Exercises for Python programming, Hashes and Salts

## Reimplement the Ping/Pong and Distributed Variable client and server
Implement the programming exercises from the last exercise class, but this time in Python3. They have been included below for convenience.

### Ping/pong
When the server receives a `ping` message, it replies with a `pong`. In all other cases the server returns `BAD REQUEST`.

### Distributed variable
The server accepts two different kinds of messages.

* `PUT [SOME STRING]` that stores a string in the internal storage of the server. Note that the first space is a separator and thus part of the protocol syntax.
* `GET` that returns the string that is stored.

When the server receives a `PUT` it saves the string to an internal variable and returns `OK`. The following `PUT` messages will not update the variable, but return `VARIABLE FILLED`.

When the server receives a `GET` it returns the stores variable. All `GET`s should be blocking, until the server has received the first `PUT`. Thus, clients sending a `GET` before another client send a `PUT` should block and wait until the server receives the first `PUT` and responds to all waiting clients.

Once you get both C and Python working, try using the C client with the Python server, and the Python client with the C server. If you've done it correctly, then they should both work just fine, as we don't care what programming language we're communicating with across the network, only that they follow the protocol we have agreed on.

## Hashing and salts
Use the provided Python code to start a server. This will prompt for a password, which it will then salt and wait for messages. You should then make additions to the c code within exercise.c so that the same password is salted and hashed. Your result will automattically be sent to the server which will verifiy that it has been done correctly.
