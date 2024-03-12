#include "inputHandle.hpp"

int InputHandle::GetUserChoice(int max){
    int choice = -1;
    while (choice < 1 || choice > max){
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()){
            std::cin.clear();
            std::string line;
            std::getline(std::cin, line);
            choice = -1;
        }
    }
    return choice;
}

std::string InputHandle::RemoveSpaces(std::string str){
    std::string newStr;
    for (char c : str)
        if (!std::isspace(c))
            newStr += c;
    return newStr;
}

bool InputHandle::CheckValidName(std::string name){
    for (char c : name)
        if (!std::isalpha(c) && c != ' ')
            return false;
    return true;
}

bool InputHandle::CheckValidID(int id){
    return id > 0;
}