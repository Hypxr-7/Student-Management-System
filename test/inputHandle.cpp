#include "inputHandle.hpp"

int GetUserChoice(int max, std::string prompt){
    int choice = -1;
    while (choice < 1 || choice > max){
        std::cout << prompt;
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

std::string GetUserInput(std::string prompt){
    std::string input;
    std::cout << prompt;
    std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}

std::string RemoveSpaces(std::string str){
    std::string newStr;
    for (char c : str)
        if (!std::isspace(c))
            newStr += c;
    return newStr;
}

bool CheckValidName(std::string name){
    for (char c : name)
        if (!std::isalpha(c) && c != ' ')
            return false;
    return true;
}

bool CheckValidID(int id){
    return id > 0;
}

std::string StripString(std::string str){
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}