#include <iostream>
#include <format>
#include "passwordManager.hpp"
#include "student.hpp"
#include "inputHandle.hpp"
#include "course.hpp"
#include "fileHandle.hpp"

int main(){

    while (true){
        bool loginStatus = false;
        int choice1, choice2, choice3;
        PasswordManager passwordManager;
        Student student("data/studentList.csv");
        Course course("data/courseList.csv");
        
        std::cout << std::format("{:^60}", "**Welcome to the Student Management System**") << std::endl << std::endl;
        std::cout << std::format("|{:^20}|{:^20}|{:^20}|", "[1] Register", "[2] Login", "[3] Exit") << std::endl;

        choice1 = GetUserChoice(3, "Enter your choice: ");

        if (choice1 == 1){
            passwordManager.RegisterUser();
            continue;
        }

        else if (choice1 == 2){
            if (passwordManager.Login())
                loginStatus = true;
            else{
                std::cout << "Login Failed" << std::endl;
                continue;
            }
        }

        else if (choice1 == 3) exit(0);


        if (loginStatus){
            std::cout << std::format("|{:^20}|{:^20}|{:^20}|", "[1] Student Info", "[2] Course Info", "[3] Log Out")<< std::endl;
            choice2 = GetUserChoice(2, "Enter your choice: ");

            if (choice2 == 3) loginStatus = false;
        }

        if (loginStatus && choice2 == 1){
            while (true){
                std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add", "[2] Display", "[3] Update Name", "[4] Delete", "[5] Back") << std::endl;

                choice3 = GetUserChoice(5, "Enter your choice: ");

                if (choice3 == 1) student.Add();
                else if (choice3 == 2) student.Display();
                else if (choice3 == 3) student.UpdateStudentName();
                else if (choice3 == 4) student.Delete();
                else if (choice3 == 5) break;
            }
        }

        if (loginStatus && choice2 == 2){
            while (true){
                std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add", "[2] Display", "[3] Update Name", "[4] Update Credit", "[5] Delete", "[6] Back") << std::endl;
                
                choice3 = GetUserChoice(5, "Enter your choice: ");

                if (choice3 == 1) course.Add();
                else if (choice3 == 2) course.Display();
                else if (choice3 == 3) course.UpdateCourseName();
                else if (choice3 == 4) course.UpadateCourseCredit();
                else if (choice3 == 5) course.Delete();
                else if (choice3 == 6) break;
            }
        }
    }

    return 0;
}