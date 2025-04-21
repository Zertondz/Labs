#include <net.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_set>
class Main_server : public Server, public Client{
private:
    int BUFF_SIZE = 1024;
    std::string check_str(std::string str){
        std::vector<std::string> words;
        std::istringstream iss(str);
        std::string word;
        std::unordered_set<std::string> seen;
        while(iss >> word){
            if(seen.find(word) == seen.end()){
                seen.insert(word);
                words.push_back(word);
            }
        }
        std::ostringstream oss;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i != 0) oss << " ";
            oss << words[i];
        }
        return oss.str();
    }
    int parser(std::vector<char> &res, int sock){
        try {
            std::string res_str(res.data());
            nlohmann::json request = nlohmann::json::parse(res_str.c_str() + res_str.find("\r\n\r\n") + 4);
            nlohmann::json response;
            std::string pop = check_str(request["message"]);
            if(pop.size() != 0){
                response["status"] = "success";
                response["received_data"] = pop;
                std::string response_str = "HTTP/1.1 200 OK\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: " + std::to_string(response.dump().size()) + "\r\n"
                "\r\n" + response.dump();
                send(client_socket, response_str.c_str(), response_str.size(), 0);
                if(send(sock, response_str.c_str(), response_str.size(), 0) < 0){
                    perror("Client output");
                    throw std::runtime_error("!!!!");
                }
            }
            else{
                std::string error_response = "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: application/json\r\n"
                "Content-Length: 61\r\n"
                "\r\n"
                "{\"status\":\"Invalid JSON\",\"message\":\"Could not parse request\"}";
                send(sock, error_response.c_str(), error_response.size(), 0);
            }

        }
        catch (nlohmann::json::parse_error& e){
            std::cout << e.what() << std::endl;
            std::string error_response = "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 61\r\n"
            "\r\n"
            "{\"status\":\"Invalid JSON\",\"message\":\"Could not parse request\"}";
            send(sock, error_response.c_str(), error_response.size(), 0);
        }
        return 0;
    }
public:
    Main_server(): Server(8080), Client(5080){}
    int start(){
        int bytes_read;
        int sock;
        std::vector<char> buf(BUFF_SIZE);
        std::vector<char> res;
        while(1)
        {
            sock = accept(server_socket, NULL, NULL);
            if(sock < 0)
            {
                perror("accept");
                close(sock);
                throw std::runtime_error("!!!!");
            }
            while(1)
            {
                bytes_read = recv(sock, buf.data(), BUFF_SIZE, 0);
                if(bytes_read <= 0) break;
                if(bytes_read < BUFF_SIZE){
                    buf[bytes_read] = 0;
                    res.insert(res.end(), buf.begin(), buf.begin() + bytes_read + 1);
                    if(std::string(res.data()) == "stop_s"){
                        std::cout << "STOP" << std::endl;
                        return 0;
                    }
                    else if(std::string(res.data()) == "stop"){
                        std::cout << "STOP" << std::endl;
                        send(client_socket, res.data(), res.size(), 0);
                        return 0;
                    }
                    parser(res, sock);
                    res.clear();
                    buf.clear();
                }
                else{
                    res.insert(res.end(), buf.begin(), buf.begin() + bytes_read);
                }
            }
            close(sock);
        }
        return 0;
    }
    ~Main_server() = default;
};