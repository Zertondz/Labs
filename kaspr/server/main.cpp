#include <iostream>
#include "server.hpp"

int main(){
    try{
        Main_server ser;
        ser.start();
    }
    catch(std::exception &e){
        std::cout <<e.what() << std::endl;
    }
    return 0;
}