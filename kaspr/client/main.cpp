#include <iostream>
#include <client.hpp>

int main(){
    try{
        Client_K men;
        men.start();
    }
    catch(std::exception &e){
        std::cout <<e.what() << std::endl;
    }
    return 0;
}