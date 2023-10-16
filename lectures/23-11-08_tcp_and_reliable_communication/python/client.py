import socket
import multiprocessing
import time

server_ip = "0.0.0.0"
server_port = 12345

def get_reply(id, result_queue, reply_socket):
    reply = reply_socket.recv(1)
    print(f"Recieved reply: {reply.decode()}")
    result_queue.put(id)

def timeout(id, result_queue):
    time.sleep(2)
    result_queue.put(id)

if __name__ == "__main__":
    timeout_queue = multiprocessing.Queue()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn_socket:
        request = 'a'

        conn_socket.connect((server_ip, server_port))
        conn_socket.sendall(request.encode())
        print(f"Sent message {request}")

        reply_process = multiprocessing.Process(target=get_reply, args=(1, timeout_queue, conn_socket), daemon=True)
        timeout_process = multiprocessing.Process(target=timeout, args=(2, timeout_queue), daemon=True)

        reply_process.start()
        timeout_process.start()

        result = timeout_queue.get()
        if result == 2:
            print(f"Could not wait for response")
        if result == 1:
            print(f"Got immediate reply")
    reply_process.terminate()
    timeout_process.terminate()
    print(f"Complete")

        

