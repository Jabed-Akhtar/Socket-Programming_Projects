import socket

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname()) # get the IPv4 address
FORMAT = 'utf-8'
DISCONNECT_MSG = "!DISCONNECT"
ADDR = (SERVER, PORT)


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)

def send(msg):
    msg = msg.encode(FORMAT)
    msg_len = len(msg)
    send_len = str(msg_len).encode(FORMAT)
    send_len += b' ' * (HEADER - len(send_len))
    client.send(send_len)
    client.send(msg)
    print(client.recv(2048).decode(FORMAT))

# sending message
send("Hello from Cleint.")
send(DISCONNECT_MSG)
