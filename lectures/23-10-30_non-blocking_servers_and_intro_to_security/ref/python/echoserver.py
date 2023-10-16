import socket
import sys

ip = sys.argv[1]
port = int(sys.argv[2])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.bind((ip, port))
    print(f"Listening on ip: {ip} port: {port}")
    server_socket.listen(True)
    while True:
        connection, address = server_socket.accept()
        while True:
            data = connection.recv(1024)
            if not data:
                break
            print(f"Received: {data}")
            if data.decode() == "ping\n":
                connection.sendall(bytearray("pong\n".encode()))
            connection.sendall(data)
        connection.close()

