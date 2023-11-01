# Exercises for CN, Application layer

## Exercises from Chapter 2 of Kurose and Ross on "Application Layer"

Review questions

* R3
Klienten initialiserer og forespørger data. Serveren serverer data.
* R4
En peer kan agerere både som server og klient
* R5
ip + port
* R10
Handshake-protocol er en etablering af forbindelse mellem to enheder før data-udveksling
* R12
E-tag kan bruges, hvis de er genereret med en hash-funktion.
* R15
HTTP har selvfølgeligt krav til headeren. Til kroppen er der ikke nogen begrænsning, men kroppens type skal defineres i headeren (content-type).
SMTP kan kun sende 7-bit Ascii. Hvis vilkårligt data skal sendes over SMTP, så skal det enkodes som ascii før det sendes, og afkodes igen efter modtagelse.

Problems

* P1
a. False. One request, one response.
b. Ja, en TCP-forbindelse kan være persistent med keep-alive-flaget.
c. En TCP-pakke er en enkelt request, så nej.
d. Falskt. Date beskriver hvornår pakken er sendt. Der er et andet HTTP-felt der hedder "last modified".
e. Nej. f.eks. vil en respons til en POST-request kun bestå af en header hvori status-feltet er "200" (OK)
* P4
a. gaia.cs.umass.edu/cs453/index.html
b. HTTP/1.1
c. Persistent (keep-alive flag)
d. Ikke synlig.
e. Mozilla/5.0 
* P5
a. Ja (status 200 OK)
b. Sat, 10 Dec2005 18:27:46
c. 3874
d. `<!doc`
* P10
Forskellen er, at for en persistent forbindelse sparer 10 handshakes.
* P13

## Programming
Browse the complete HTTP RFC and convince yourself that it is too long to read entirely. It can be found here: https://www.rfc-editor.org/rfc/rfc2616

Now create a simple, HTTP complient request client. It must be capable of sending GET or HEAD requests and only needs to send the Request-Line (section 5.1 of the RFC) with no accompanying message-body or headers. Send your messages to the non-replying server for feedback on if you've done it correctly. 

Optionally, send your request to the replying server to parse and print the response in C. In either case you should assemble your requests in C and parse and response to be printed. Do not simply input one long string to create a request, actually take the different parts (e.g. the method, request-uri and http-version) and join them together to form the request. Similarly, do not just print the entirety of the feedback but identify the seperate parts. Python clients have also been provided as inspiration and a guide, though do remember that just because some logic works in python does not mean it is a good idea to directly copy to C.
