#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdexcept>
#include <thread>

constexpr const char* PORT = "8888";
constexpr int BUFFER_SIZE = 512;

class WinSock
{
public:
    WinSock()
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
            throw std::runtime_error("WSAStartup failed");
    }
    ~WinSock()
    {
        WSACleanup();
    }
private:
    WSADATA wsa{};
};

void handle_client(SOCKET client_sock)
{
    char buffer[BUFFER_SIZE];
    int recv_size;

    std::cout << "[+] Client thread started\n";

    while ((recv_size = recv(client_sock, buffer, BUFFER_SIZE - 1, 0)) > 0)
    {
        buffer[recv_size] = '\0';
        std::cout << "Client: " << buffer << '\n';

        // Echo back
        send(client_sock, buffer, recv_size, 0);
    }

    std::cout << "[-] Client disconnected\n";
    closesocket(client_sock);
}

int main()
{
    try
    {
        WinSock winsock;

        addrinfo hints{}, *res = nullptr;
        hints.ai_family   = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags    = AI_PASSIVE;

        getaddrinfo(nullptr, PORT, &hints, &res);

        SOCKET listen_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listen_sock == INVALID_SOCKET)
            throw std::runtime_error("Socket creation failed");

        if (bind(listen_sock, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR)
            throw std::runtime_error("Bind failed");

        freeaddrinfo(res);

        if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR)
            throw std::runtime_error("Listen failed");

        std::cout << "Server listening on port " << PORT << "...\n";

        while (true)
        {
            SOCKET client_sock = accept(listen_sock, nullptr, nullptr);
            if (client_sock == INVALID_SOCKET)
            {
                std::cerr << "Accept failed\n";
                continue;
            }

            std::thread(handle_client, client_sock).detach();
        }

        closesocket(listen_sock);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
