
import socket
import socketserver
import struct
import threading
import time

class ExerciseServer(socketserver.ThreadingTCPServer):
    def __init__(self, ip, port, handler):
        super().__init__((ip, port), handler)


def threaded_client(peer_ip, peer_port, to_send):
    loop_counter = 0
    while True:
        try:
            print(f"C - [{loop_counter}] Connecting to client at: "
                  f"{peer_ip}:{peer_port}")
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn_socket:
                conn_socket.connect((peer_ip, peer_port))

                message = bytearray()
                message.extend(struct.pack('!I', len(to_send)))
                message.extend(bytes(to_send, 'ascii'))

                conn_socket.sendall(message)
        except ConnectionRefusedError:
            print(f"C - [{loop_counter}] Couldn't connect to "
                  f"{peer_ip}:{peer_port}. Will try again in 5 seconds.")
        time.sleep(5)
        loop_counter+=1


class NodeHandler(socketserver.StreamRequestHandler):
    def handle(self):
        request_header = self.request.recv(4)
        request_length = struct.unpack('!I', request_header)[0]
        
        payload = self.request.recv(request_length)

        print(f"S - Recieved message: {payload.decode('ascii')}")


if __name__ == "__main__":
    my_ip = "127.0.0.1"
    my_port = 12345

    peer_ip = "127.0.0.1"
    peer_port = 23456

    message = f"Hello from {my_ip}:{my_port}\0"

    client_thread = threading.Thread(
        target=threaded_client, 
        args=(peer_ip, peer_port, message), 
        daemon=True
    )
    client_thread.start()

    print(f"S - Starting server at: {my_ip}:{my_port}")
    # Start server side
    with socketserver.ThreadingTCPServer((my_ip, my_port), NodeHandler) as server:
        try: 
            server.serve_forever()
        finally:
            server.server_close()
