import socket

SERVER_IP = "127.0.0.1"
PORT = 8888
BUFFER_SIZE = 512

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((SERVER_IP, PORT))
        print("Connected to server. Type messages:")

        while True:
            msg = input("> ")
            if msg == "exit":
                break

            sock.sendall(msg.encode())

            data = sock.recv(BUFFER_SIZE)
            if not data:
                break

            print(f"Server echoed: {data.decode()}")

if __name__ == "__main__":
    main()
