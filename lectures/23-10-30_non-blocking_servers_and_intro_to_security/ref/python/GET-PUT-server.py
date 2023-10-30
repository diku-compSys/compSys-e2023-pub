import socket
import threading
import sys
import re

ip = sys.argv[1]
port = int(sys.argv[2])
lock = threading.Lock() #
cond = threading.Condition(lock) #Create python like condition vrb (includes MUTEX lock), but we use one explicitly created

internal_save = None
stored = False

#Not used at the moment
def print_client_info(connection,address):
    host_name = socket.gethostbyaddr(address[0])
    print(host_name)


def handle_request(connection):
    global internal_save
    global stored
    while True:
        data = connection.recv(1024)
        if not data:
            print(f"Connection with {address[0]}:{address[1]} closed!")
            break
        print(f"Received: {data} from user {address[0]}:{address[1]}")
        decoded = data.decode()
        pattern = r'(\w+)\s(\w+)|(GET)' #Match cases specified by a REGEX
        match = re.match(pattern,decoded)
        if match:
            input1 = match.group(1)
            input2 = match.group(2)
            input3 = match.group(3)
            if (input1 == "PUT" and not(stored)):
                with cond: #Acuiring lock when accessing shared ressource
                    internal_save = input2
                    stored = True
                    cond.notify_all()
                connection.sendall(bytearray("OK".encode()))
            elif(input1 == "PUT" and (stored)):
                with cond: #Lock again when accessing shared vrb
                    connection.sendall(bytearray("VARIABLE FILLED".encode()))
            elif(input3 == "GET" and (stored)):
                connection.sendall(bytearray(internal_save.encode()))
            elif(input3 == "GET" and not(stored)):
                with cond: #Lock part of cond object., encapsulated in with block makes sure to aquire lock
                    while not(stored):
                        connection.sendall(bytearray("BLOCKED - WAIT...\n".encode()))
                        cond.wait()
                    connection.sendall(bytearray(internal_save.encode()))
        else:
            connection.sendall(bytearray("Request format not support".encode()))
    return 

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) #Can resuse port upon rerun
    server_socket.bind((ip, port))
    print(f"Listening on ip: {ip} port: {port}")
    server_socket.listen(True)
    while True:
        connection, address = server_socket.accept() #Accepts a new connection, assigning connection as the C "FILE descriptor"
        client_handler = threading.Thread(target=handle_request, args=(connection,))
        client_handler.start()
