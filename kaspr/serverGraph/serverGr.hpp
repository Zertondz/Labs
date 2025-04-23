#include <net.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif
class Graph_server : public Server{
private:
    const int BUFF_SIZE = 10;
public:
    Graph_server() : Server(){}
    int start(){
        #ifdef _WIN32
            SOCKET sock;
        #else
            int sock;
        #endif
        int bytes_read;
        std::vector<char> buf(BUFF_SIZE);
        std::vector<char> res;
        while(true){
            sock = accept(server_socket, NULL, NULL);
            #ifdef _WIN32
            if (sock == INVALID_SOCKET) {
                std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
                closesocket(sock);
                throw std::runtime_error("!!!");
            }
            #else
            if (sock < 0) {
                perror("accept");
                close(sock);
                throw std::runtime_error("!!!");
            }
            #endif
            while(true){
                bytes_read = recv(sock, buf.data(), BUFF_SIZE, 0);
                if(bytes_read <= 0) break;
                if(bytes_read < BUFF_SIZE){
                    buf[bytes_read] = 0;
                    res.insert(res.end(), buf.begin(), buf.begin() + bytes_read + 1);
                    std::string mes(res.data());
                    if (mes == "stop") {
                        #ifdef _WIN32
                            closesocket(sock);
                        #else
                            close(sock);
                        #endif
                        return 0;
                    }
                    nlohmann::json req = nlohmann::json::parse(mes.data() + mes.find("\r\n\r\n") + 4);
                    if(req["status"] == "success"){
                        std::cout << "message : " << req["received_data"] << std::endl;;
                    }
                    res.clear();
                    buf.clear();
                }
                else{
                    res.insert(res.end(), buf.begin(), buf.begin() + bytes_read);
                }
            }
            #ifdef _WIN32
            closesocket(sock);
            #else
            close(sock);
            #endif
        }
        return 0;
    }
    ~Graph_server() = default;
};