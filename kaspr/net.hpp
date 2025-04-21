#include <iostream>
#include <limits>
#include <cstring>
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
    int server_socket;
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
public:
    Server(int port_si = 5080) : port_s(port_si){
        setup();
        #ifdef _WIN32
            #include <ws2tcpip.h>
            #include <winsock2.h>
            #include <windows.h>
        #else
        struct sockaddr_in addr;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(server_socket < 0){
            perror("socket");
            close(server_socket);
            throw std::runtime_error("!!!!");
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_s);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if(bind(server_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0){
            perror("bind");
            close(server_socket);
            throw std::runtime_error("!!!!");
        }
        listen(server_socket, size_deque_client);
        #endif
    }
    ~Server(){
        close(server_socket);
    }
};
class Client{
protected:
    std::string servername = "localhost";
    int port_c;
    int client_socket;
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
    Client(int port_ci = 8080) : port_c(port_ci){
        setup();
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1){
            perror("socket() failed");
            throw std::runtime_error("!!!!");
        }
        struct sockaddr_in addr;
        struct addrinfo hints;
        struct addrinfo *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(servername.c_str(), NULL, &hints, &res) != 0) {
            perror("Host lookup failed");
            throw std::runtime_error("!!!");
        }
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_c);
        addr.sin_addr = reinterpret_cast<struct sockaddr_in*>(res->ai_addr)->sin_addr;
        if(connect(client_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0){
            perror("Connect");
            freeaddrinfo(res);
            throw std::runtime_error("!!!");
        }
    }
    ~Client(){
        close(client_socket);
    }
};