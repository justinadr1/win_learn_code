#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr const char* PORT      = "8888";
constexpr int BUFFER_SIZE       = 512;

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

int main()
{
    try 
    {
        WinSock winsock;

        addrinfo hints{}, *res = nullptr;
        hints.ai_family   = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        getaddrinfo(SERVER_IP, PORT, &hints, &res);

        SOCKET sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock == INVALID_SOCKET)
            throw std::runtime_error("Socket creation failed");

        if (connect(sock, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR)
            throw std::runtime_error("Connect failed");

        freeaddrinfo(res);

        std::cout << "Connected to server. Type messages (exit to quit):\n";

        std::string message;
        char buffer[BUFFER_SIZE];

        while (true) 
        {
            std::cout << "> ";
            std::getline(std::cin, message);

            if (message == "exit")
                break;

            send(sock, message.c_str(), (int)message.size(), 0);

            int recv_size = recv(sock, buffer, BUFFER_SIZE - 1, 0);
            if (recv_size <= 0)
                break;

            buffer[recv_size] = '\0';
            std::cout << "Server echoed: " << buffer << '\n';
        }

        closesocket(sock);
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
