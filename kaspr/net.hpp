#ifndef UNIQUE_NAME_FOR_HEADER
#define UNIQUE_NAME_FOR_HEADER
#include <iostream>
#include <limits>
#include <cstring>
#include <vector>
#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <netdb.h>
#endif
class Server{
protected:
    int port_s = 5080;
    int size_deque_client = 1;
    #ifdef _WIN32
    SOCKET server_socket;
    #else
    int server_socket;
    #endif
private:
    int setup(){
        int num = -1;
        while(1){
            std::cout <<"=======SERVER SETUP=======\n" <<
            "(1) Client's port: " << port_s << "\n" <<
            "(2) Client deque size : "<< size_deque_client <<"\n" <<
            "(3) Exit and start\n" <<
            "Change: ";
            std::cin >> num;
            if(std::cin.eof()){
                throw std::runtime_error("The input is finished!!!");
            }
            if(std::cin.bad()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            else if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            if (std::cin.peek() != '\n') {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            switch (num){
                case 1:
                    int mem_port;
                    std::cout << "Enter the port number : ";
                    std::cin >> mem_port;
                    if(std::cin.bad() or std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    if (std::cin.peek() != '\n') {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    port_s = mem_port;
                    std::cout << std::endl;
                    break;
                case 2:
                    int mem_size;
                    std::cout << "Enter the deque size : ";
                    std::cin >> mem_size;
                    if(std::cin.bad() or std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    if (std::cin.peek() != '\n') {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    port_s = mem_size;
                    std::cout << std::endl;
                    break;
                case 3:
                    return 0;
                    break;
                default:
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Incorrect format" << std::endl;
                    break;
            }
        }
        return 0;
    }
    const int BUFF_SIZE = 1024;
    std::vector<char> buf = std::vector<char>(BUFF_SIZE);
    std::vector<char> res;        
    int sock;
    int bytes_read;
public:
    Server(int port_si = 5080) : port_s(port_si){
        //setup();
        #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }
        #endif
        struct sockaddr_in addr;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        #ifdef _WIN32
        if (server_socket == INVALID_SOCKET) {
            std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
            throw std::runtime_error("socket creation failed");
        }
        #else
        if (server_socket < 0) {
            perror("socket");
            close(server_socket);
            throw std::runtime_error("socket creation failed");
        }
        #endif
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_s);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if(bind(server_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0){
            #ifdef _WIN32
            std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
            closesocket(server_socket);
            WSACleanup();
            #else
            perror("bind");
            close(server_socket);
            #endif
            throw std::runtime_error("bind failed");
        }
        if (listen(server_socket, SOMAXCONN) < 0) {
            #ifdef _WIN32
            std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
            closesocket(server_socket);
            WSACleanup();
            #else
            perror("listen");
            close(server_socket);
            #endif
            throw std::runtime_error("listen failed");
        }
    }
    ~Server() {
        #ifdef _WIN32
        closesocket(server_socket);
        WSACleanup();
        #else
        close(server_socket);
        #endif
    }
};
class Client{
protected:
    std::string servername = "127.0.0.1";
    int port_c;
    #ifdef _WIN32
    SOCKET client_socket;
    #else
    int client_socket;
    #endif
private:
    int setup(){
        int num = -1;
        while(1){
            std::cout << "=======CLIENT SETUP=======\n" <<
            "(1) Client's port: " << port_c << "\n" <<
            "(2) Server name : "<< servername <<"\n" <<
            "(3) Exit and start of connection\n" <<
            "Change: ";
            std::cin >> num;
            if(std::cin.eof()){
                throw std::runtime_error("The input is finished!!!");
            }
            if(std::cin.bad()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            else if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            if (std::cin.peek() != '\n') {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect format" << std::endl;
                continue;
            }
            switch (num){
                case 1:
                    int mem_port;
                    std::cout << "Enter the port number : ";
                    std::cin >> mem_port;
                    if(std::cin.bad() or std::cin.fail()){
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    if (std::cin.peek() != '\n') {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Incorrect format" << std::endl;
                        break;
                    }
                    port_c = mem_port;
                    std::cout << std::endl;
                    break;
                case 2:
                    std::cout << "Enter the servername : ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, servername);
                    std::cout << std::endl;
                    break;
                case 3:
                    return 0;
                    break;
                default:
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Incorrect format" << std::endl;
                    std::cin.clear();
                    break;
            }
        }
        return 0;
    }
public:
    void send_request(std::string mes){
        send(client_socket, mes.c_str(), mes.size(), 0);
    }
    Client(int port_ci = 8080) : port_c(port_ci){
        //setup();
        #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }
        #endif
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        #ifdef _WIN32
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
            throw std::runtime_error("socket creation failed");
        }
        #else
        if (client_socket == -1) {
            perror("socket() failed");
            throw std::runtime_error("socket creation failed");
        }
        #endif
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        struct sockaddr_in addr;
        if (getaddrinfo(servername.c_str(), NULL, &hints, &res) != 0) {
            #ifdef _WIN32
            std::cerr << "Host lookup failed: " << WSAGetLastError() << std::endl;
            closesocket(client_socket);
            WSACleanup();
            #else
            perror("Host lookup failed");
            close(client_socket);
            #endif
            throw std::runtime_error("Host resolution failed");
        }
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_c);
        addr.sin_addr = reinterpret_cast<struct sockaddr_in*>(res->ai_addr)->sin_addr;
        if(connect(client_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0){
            #ifdef _WIN32
            std::cerr << "Connect failed: " << WSAGetLastError() << std::endl;
            closesocket(client_socket);
            WSACleanup();
            #else
            perror("Connect client");
            close(client_socket);
            #endif
            freeaddrinfo(res);
            throw std::runtime_error("Connection failed");
        }
        freeaddrinfo(res);
    }
    ~Client(){
        #ifdef _WIN32
        closesocket(client_socket);
        WSACleanup();
        #else
        close(client_socket);
        #endif
    }
};
#endif