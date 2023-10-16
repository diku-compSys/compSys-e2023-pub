import hashlib
import socketserver

class ExerciseServer(socketserver.ThreadingTCPServer):
    def __init__(self, ip: str, port: int, 
            handler: socketserver.StreamRequestHandler):
        super().__init__((ip, port), handler)

        password = input("Enter password: ")
        salt = "0123456789012345678901234567890123456789012345678901234567890123"
        salted = password + salt

        self.target = hashlib.sha256(salted.encode()).digest()

class Handler(socketserver.StreamRequestHandler):
    def handle(self):
        bytes_message = self.request.recv(1024)

        if bytes_message == self.server.target:
            print("Password was successfully salted, hashed and sent")
        else:
            print("Hashes differ:")
            print("\t", bytes_message)
            print("vs")
            print("\t", self.server.target)

if __name__ == "__main__":
    ip = '0.0.0.0'
    port = 12345

    with ExerciseServer(ip, port, Handler) as exercise_server:
        try:
            exercise_server.serve_forever()
        finally:
            exercise_server.server_close()