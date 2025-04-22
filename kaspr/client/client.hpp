#include <net.hpp>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <poll.h>
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
        struct pollfd pfd;
        pfd.fd = client_socket;
        pfd.events = POLLOUT | POLLERR | POLLHUP;;
        std::string mes;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(1){
            int ret = poll(&pfd, 1, timeout_ms);
            if (ret == -1) {
                perror("Ошибка poll");
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
                    std::cout<< "Enter line (enter stop to stop all servers or stop_s to stop main server): " ;
                    std::getline(std::cin, mes);
                    if(std::cin.eof()){
                        break;
                    }
                    if(mes == "stop"){
                        send(client_socket, mes.c_str(), mes.size(), 0);
                    }
                    else if(mes == "stop_s"){
                        send(client_socket, mes.c_str(), mes.size(), 0);
                    }
                    else{
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