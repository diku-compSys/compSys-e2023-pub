import socket
import sys
ip = sys.argv[1]
port = int(sys.argv[2])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
  client_socket.connect((ip, port))

  while True:
    request = input()
    request = bytearray((request + "\n").encode())
    client_socket.sendall(request)
    response = client_socket.recv(1024)
    response = response.decode()
    print(response)
