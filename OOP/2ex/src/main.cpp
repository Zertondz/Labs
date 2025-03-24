// #include <iostream>
// #include "Detail.h"
// #include "DialogFunctions.h"

// int main() {
//     // Создаем объект детали
//     Detail detail;
//     // Взаимодействие с пользователем через диалоговые функции
//     interactWithDetail(detail);
//     // Вывод информации о детали
//     std::cout << detail << "\n\n";
    
//     // Проверка оператора  spaceship
//     // Создаем два объекта Detail

//     Detail detail1("A-Part");
//     Detail detail2("B-Part");
//     Detail detail3("A-Part");

//     // Сравниваем объекты, используя различные операторы сравнения
//     std::cout << "Comparing detail1 (A-Part) and detail2 (B-Part):\n";
//     std::cout << "detail1 < detail2: " << (detail1 < detail2 ? "true" : "false") << std::endl;
//     std::cout << "detail1 > detail2: " << (detail1 > detail2 ? "true" : "false") << std::endl;
//     std::cout << "detail1 <= detail2: " << (detail1 <= detail2 ? "true" : "false") << std::endl;
//     std::cout << "detail1 >= detail2: " << (detail1 >= detail2 ? "true" : "false") << std::endl;

//     std::cout << "\nComparing detail1 (A-Part) and detail3 (A-Part):\n";
//     std::cout << "detail1 < detail3: " << (detail1 < detail3 ? "true" : "false") << std::endl;
//     std::cout << "detail1 > detail3: " << (detail1 > detail3 ? "true" : "false") << std::endl;
//     std::cout << "detail1 <= detail3: " << (detail1 <= detail3 ? "true" : "false") << std::endl;
//     std::cout << "detail1 >= detail3: " << (detail1 >= detail3 ? "true" : "false") << std::endl;


//     return 0;
// }




#include <iostream>
#include <fstream>
#include <string>
#include "AssemblyInstruction.h"
#include "pric.h"
int main() {
    std::string line;
    try {
        while(1)
        {
            std::cout <<"(1)Доступные инструкции\n"
                        "(2)Узнать инструкции\n"
                        "Введите пункт: ";
            std::getline(std::cin, line);
            switch (std::stoi(line))
            {
            case 1:
                check_instr();
                break;
            case 2:
                now_instr();
                break;
            default:
                break;
            }
        }
        AssemblyInstruction instruction(create_instructtion());
        std::cout << instruction.getAssemblyInstructions() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}
