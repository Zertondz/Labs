#include <net.hpp>
#include <nlohmann/json.hpp>
#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
    #include <windows.h>
    #include <winsock2.h>
    #include <mstcpip.h>
    #include <ws2def.h>
    #include <ws2ipdef.h>
    #define _WIN32_WINNT 0x0600
#else
    #include <poll.h>
    #include <unistd.h>
#endif
class Client_K : public Client{
private:
    const int BUFF_SIZE = 1024;
    const std::string create_http_json(std::string &mes){
        nlohmann::json request;
        request["message"] = mes;
        request["action"] = "get_data";
        std::string request_str = "POST / HTTP/1.1\r\n"
        "Host: " + servername + "\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: " + std::to_string(request.dump().size()) + "\r\n"
        "\r\n" + request.dump();
        return request_str;
    }
public:
    Client_K(int port_c = 8080) : Client(port_c) {}
    void send_request(std::string mes){
        if(mes != "stop"){
            mes = create_http_json(mes);
        }
        send(client_socket, mes.c_str(), mes.size(), 0);
        std::vector<char> buf(BUFF_SIZE);
        std::vector<char> res;
        int bytes_read;
        while(1)
        {
            bytes_read = recv(client_socket, buf.data(), BUFF_SIZE, 0);
            if(bytes_read <= 0) break;
            if(bytes_read < BUFF_SIZE){
                buf[bytes_read] = 0;
                res.insert(res.end(), buf.begin(), buf.begin() + bytes_read + 1);
                //std::string res_str(res.data());
                //nlohmann::json request = nlohmann::json::parse(res_str.c_str() + res_str.find("\r\n\r\n") + 4);
                //std::cout << "Status : " << request["status"] << std::endl;
                res.clear();
                buf.clear();
                break;
            }
            else{
                res.insert(res.end(), buf.begin(), buf.begin() + bytes_read);
            }
        }
    }
    int start(){
        int timeout_ms = 5000;
        std::string mes;
        #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed");
        }
        
        WSAPOLLFD pfd = {};
        pfd.fd = client_socket;
        pfd.events = POLLOUT | POLLERR | POLLHUP;
        #else
        struct pollfd pfd;
        pfd.fd = client_socket;
        pfd.events = POLLOUT | POLLERR | POLLHUP;
        #endif
        while(1){
            #ifdef _WIN32
            std::cout << "client_socket: " << client_socket << std::endl;
            if (client_socket == INVALID_SOCKET) {
                std::cerr << "Invalid client socket!" << std::endl;
                return -1;
            }
            int ret = WSAPoll(&pfd, 1, timeout_ms);
            #else
            int ret = poll(&pfd, 1, timeout_ms);
            #endif
            if (ret == -1) {
                #ifdef _WIN32
                std::cerr << "WSAPoll error: " << WSAGetLastError() << std::endl;
                WSACleanup();
                #else
                perror("Ошибка poll");
                close(client_socket);
                #endif
                throw std::runtime_error("!!!");
            }
            else if (ret > 0) {
                if (pfd.revents & POLLHUP) {
                    throw std::runtime_error("Сервер отключился (POLLHUP)\n");
                }
                else if (pfd.revents & POLLERR) {
                    throw std::runtime_error("Ошибка сокета (POLLERR)\n");
                }
                if (pfd.revents & POLLOUT) {
                    std::cout << "Enter line (enter stop to stop all servers or stop_s to stop main server): ";
                    std::getline(std::cin, mes);
                    
                    if(std::cin.eof()) {
                        break;
                    }
                    
                    if(mes == "stop" || mes == "stop_s") {
                        send(client_socket, mes.c_str(), mes.size(), 0);
                    }
                    else {
                        std::string res = create_http_json(mes);
                        send(client_socket, res.c_str(), res.size(), 0);
                    }
                }
                std::vector<char> buf(BUFF_SIZE);
                std::vector<char> res;
                int bytes_read;
                while(1)
                {
                    bytes_read = recv(client_socket, buf.data(), BUFF_SIZE, 0);
                    if(bytes_read <= 0) break;
                    if(bytes_read < BUFF_SIZE){
                        buf[bytes_read] = 0;
                        res.insert(res.end(), buf.begin(), buf.begin() + bytes_read + 1);
                        std::string res_str(res.data());
                        nlohmann::json request = nlohmann::json::parse(res_str.c_str() + res_str.find("\r\n\r\n") + 4);
                        std::cout << "Status : " << request["status"] << std::endl;
                        res.clear();
                        buf.clear();
                        break;
                    }
                    else{
                        res.insert(res.end(), buf.begin(), buf.begin() + bytes_read);
                    }
                }
            }
        }
        return 0;
    }
    ~Client_K() = default;
};