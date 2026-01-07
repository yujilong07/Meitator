#include <iostream>
#include <string>

#include "logo.hpp"


enum class MenuOption{
    DocxToPDF,
    PDFtoDocx,
    Exit
};

void greetings(int choice){
    for(int i = 0; i < 5; i++) {
        std::cout << MEITATOR_LOGO[i] << std::endl;
    }
    std::cout << "============================================" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Welcome to file extension changer!" <<std::endl;
    std::cout << "Choose your option:" << std::endl;
    std::cout << "    0: DocxToPDF" << std::endl;
    std::cout << "    1: PDFtoDocx" << std::endl;
    std::cout << "    3: Exit" << std::endl;
    std:: cout << "Enter choice (1-3): ";

    while(choice != 3){
        switch (choice){
            case 0:
                //todo 
            case 1:
                //todo
            case 2:
                break;
        }
    }

}

int main(){

}