# Exercises for CN, Application layer

## Exercises from Chapter 2 of Kurose and Ross on "Application Layer"

Review questions

* R3
* R4
* R5
* R10
* R12
* R15

Problems

* P1
* P4
* P5
* P10
* P13

## Programming
Browse the complete HTTP RFC and convince yourself that it is too long to read entirely. It can be found here: https://www.rfc-editor.org/rfc/rfc2616

Now create a simple, HTTP complient request client. It must be capable of sending GET or HEAD requests and only needs to send the Request-Line (section 5.1 of the RFC) with no accompanying message-body or headers. Send your messages to the non-replying server for feedback on if you've done it correctly. 

Optionally, send your request to the replying server to parse and print the response in C. In either case you should assemble your requests in C and parse and response to be printed. Do not simply input one long string to create a request, actually take the different parts (e.g. the method, request-uri and http-version) and join them together to form the request. Similarly, do not just print the entirety of the feedback but identify the seperate parts. Python clients have also been provided as inspiration and a guide, though do remember that just because some logic works in python does not mean it is a good idea to directly copy to C.
