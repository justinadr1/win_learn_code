import socket
import threading

HOST = "0.0.0.0"
PORT = 8888
BUFFER_SIZE = 512

def handle_client(client_sock, addr):
    print(f"[+] Client connected: {addr}")

    with client_sock:
        while True:
            data = client_sock.recv(BUFFER_SIZE)
            if not data:
                break

            message = data.decode()
            print(f"[{addr}] {message}")

            client_sock.sendall(data)

    print(f"[-] Client disconnected: {addr}")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_sock:
        server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_sock.bind((HOST, PORT))
        server_sock.listen()

        print(f"Server listening on port {PORT}...")

        while True:
            client_sock, addr = server_sock.accept()

            thread = threading.Thread(
                target=handle_client,
                args=(client_sock, addr),
                daemon=True
            )
            thread.start()

if __name__ == "__main__":
    main()
