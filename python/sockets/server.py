import socket

HOST = "0.0.0.0"   # equivalent to AI_PASSIVE
PORT = 8888
BUFFER_SIZE = 512

def main():
    # Create TCP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as listen_sock:
        listen_sock.bind((HOST, PORT))
        listen_sock.listen(1)

        print(f"Server listening on port {PORT}...")

        # Accept client
        client_sock, addr = listen_sock.accept()
        with client_sock:
            print(f"Client connected from {addr}")

            while True:
                data = client_sock.recv(BUFFER_SIZE)
                if not data:
                    break

                message = data.decode()
                print(f"Client: {message}")

                # Echo back
                client_sock.sendall(data)

        print("Client disconnected")

if __name__ == "__main__":
    main()
