#include <iostream>
#include <format>
#include "passwordManager.hpp"
#include "student.hpp"
#include "inputHandle.hpp"
#include "course.hpp"
#include "fileHandle.hpp"

int main(){
    bool loginStatus = false;

    while (true){
        PasswordManager passwordManager;
        Student student("data/studentList.csv");
        Course course("data/courseList.csv");
        
        std::cout << std::format("{:^60}", "**Welcome to the Student Management System**") << std::endl << std::endl;
        std::cout << std::format("|{:^20}|{:^20}|{:^20}|", "[1] Register", "[2] Login", "[3] Exit") << std::endl;

        int choice = GetUserChoice(3, "Enter your choice: ");

        if (choice == 1){
            passwordManager.RegisterUser();
            continue;
        }

        else if (choice == 3)
            exit(0);

        else if (choice == 2){
            if (passwordManager.Login())
                loginStatus = true;
            else{
                std::cout << "Login Failed" << std::endl;
                continue;
            }
        }

        while (loginStatus){
            std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add Student", "[2] Add Course", "[3] View Student List", "[4] View Course List", "[5] Logout") << std::endl;
            int choice = GetUserChoice(5, "Enter your choice: ");

            if (choice == 1){
                student.Add();
            }

            else if (choice == 2){
                course.Add();
            }

            else if (choice == 3){
                student.Display();
            }

            else if (choice == 4){
                course.Display();
            }

            else if (choice == 5){
                loginStatus = false;
                break;
            }
        }
    }

    return 0;
}