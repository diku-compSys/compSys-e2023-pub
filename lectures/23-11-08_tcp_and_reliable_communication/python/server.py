
import random
import socketserver
import time

server_ip = "0.0.0.0"
server_port = 12345


class NodeHandler(socketserver.StreamRequestHandler):
    def handle(self):
        request = self.request.recv(1)
        print(f"Recieved request: {request.decode()}")

        timeout = random.randrange(2)

        if timeout:
            print("Timing out...")
            time.sleep(5)
            self.request.sendall(request)
        else:
            print("No timeout")
            self.request.sendall(request)
            pass


class ExerciseServer(socketserver.ThreadingTCPServer):
    def __init__(self, ip, port, handler):
        super().__init__((ip, port), handler)


if __name__ == "__main__":
    print(f"Starting server at: {server_ip}:{server_port}")
    with ExerciseServer(server_ip, server_port, NodeHandler) as server:
        try: 
            server.serve_forever()
        finally:
            server.server_close()