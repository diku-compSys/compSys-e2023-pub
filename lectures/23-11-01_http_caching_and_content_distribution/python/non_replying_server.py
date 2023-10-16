import http.server
import socketserver


class ExerciseServer(socketserver.ThreadingTCPServer):
    def __init__(self, ip: str, port: int, 
            handler: socketserver.StreamRequestHandler):
        super().__init__((ip, port), handler)

class Handler(http.server.BaseHTTPRequestHandler):   
    def do_GET(self):
        self.verify(self.command)

    def do_HEAD(self):
        self.verify(self.command)

    def verify(self, method:str):
        if self.command not in ["GET", "HEAD"]:
            print(f"Unrecongnised command {self.command}")
            return

        if self.request_version not in ["HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"]:
            print(f"Unrecongnised version number {self.request_version}")
            return

        if not self.path:
            print("Should specify a path")

        print(f"{method} request formatted correctly")        


if __name__ == "__main__":
    ip = '0.0.0.0'
    port = 12345

    http_server = http.server.ThreadingHTTPServer((ip, port), Handler)
    http_server.serve_forever()
