import threading
from socketserver import ThreadingTCPServer, StreamRequestHandler
import sys

var = None
mutex = threading.Lock()
cond = threading.Condition(mutex)

class MyHandler(StreamRequestHandler):
  def handle(self) -> None:
    global var
    global mutex
    global cond   

    while True:
      message = self.request.recv(1024)
      if not message:
        break
      message = message.decode()
      print("Received message:", message)

      if (message[0:4] == "PUT " and len(message) != 5):
        mutex.acquire()
        if (var):
          response = "VARIABLE FILLED"
        else:
          var = message[4:]
          response = "OK"
          cond.notify_all()
        mutex.release()

      elif (message == "GET\n"):
        mutex.acquire()
        while (not var):
          cond.wait()
        response = var
        mutex.release()
           
      
      elif message == "ping\n":
        response = "pong"
      else:
        response = message
      print(f"Response: {response}")      
      response = bytearray(response.encode())
      self.request.sendall(response)
      


with ThreadingTCPServer((str(sys.argv[1]), int(sys.argv[2])), MyHandler) as my_server:
  my_server.serve_forever()


