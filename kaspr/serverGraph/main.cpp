#include <iostream>
#include <serverGr.hpp>

int main(){
    try{
        Graph_server ser;
        ser.start();
    }
    catch(std::exception &e){
        std::cout <<e.what() << std::endl;
    }
    return 0;
}