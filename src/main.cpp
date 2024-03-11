#include <iostream>
#include <iomanip>
#include <format>
#include <cstdlib>
#include "passwordManager.hpp"


// Asks user for a number between 1 and max 
// repeats until user enters a valid number
int GetUserNumber(int max){
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

int main(){
    std::cout << std::format("{:^60}", "**Welcome to the Student Management System**") << std::endl << std::endl;
    std::cout << std::format("|{:^20}|{:^20}|{:^20}|", "[1] Register", "[2] Login", "[3] Exit") << std::endl;
    
    int choice = GetUserNumber(3);

    switch (choice){
        case 1:
            std::cout << "Register" << std::endl;
            break;
        case 2:
            std::cout << "Login" << std::endl;
            break;
        case 3:
            std::cout << "Exit" << std::endl;
            exit(0);
          break;
        default:
            std::cout << "Something Wrong Happened :(" << std::endl;
            exit(1);
    } 

    

    return 0;
}