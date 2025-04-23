#include <iostream>
#include <client.hpp>

int main(){
    try{
        Client_K men;
        men.send_request("pip pop");
        men.send_request("pop");
        men.start();
    }
    catch(std::exception &e){
        std::cout <<e.what() << std::endl;
    }
    return 0;
}