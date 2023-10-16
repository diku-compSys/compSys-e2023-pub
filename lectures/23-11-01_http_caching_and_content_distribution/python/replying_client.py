import socket

GET = "GET"
HEAD = "HEAD"

SERVER = "Server: "
DATE = "Date: "

class Server(object):
    def __init__(self, ip: str, port: int):
        self.ip = ip
        self.port = port

    def send(self, method, send_str):
        if method == GET:
            send_bytes = self.build_get_request(send_str, {})
        else:
            send_bytes = self.build_head_request(send_str, {})
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn_socket:
            conn_socket.connect((self.ip, self.port))
            conn_socket.sendall(send_bytes)

            response_bytes = conn_socket.recv(1024)
            response_str = response_bytes.decode()

            response_lines = response_str.split("\r\n")
            version, code, status = response_lines[0].split(' ')

            server = ""
            date = ""
            for line in response_lines:
                if line.startswith(SERVER):
                    server = line.replace(SERVER, '')
                elif line.startswith(DATE):
                    date = line.replace(DATE, '')
                    
            print(f"Response was {code}/{status} in accordance with {version}")
            if server:
                print(f"Served by: {server}")
            if date:
                print(f"Served at: {date}")

    def build_get_request(self, req_url: str, headers: dict) -> bytearray:
        return self._build_request("GET", req_url, "HTTP/1.1", headers)

    def build_head_request(self, req_url: str, headers: dict) -> bytearray:
        return self._build_request("HEAD", req_url, "HTTP/1.1", headers)

    def _build_request(self, req_method: str, req_url: str, req_version: str,
                       headers: dict) -> bytearray:
        request = bytearray(f"{req_method} {req_url} {req_version}\r\n"
                            f"".encode())
        for header_key, header_value in headers.items():
            request.extend(bytes(
                f"{header_key}: {header_value}\r\n\r\n", 'ascii'))
        request.extend(bytes("\r\n", 'ascii'))
        return request

server = Server('0.0.0.0', 12345)
server.send(HEAD, "/index.txt")
server.send(GET, "/index.html")