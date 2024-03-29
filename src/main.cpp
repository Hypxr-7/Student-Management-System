#include <iostream>
#include <format>
#include <stdlib.h>
#include "passwordManager.hpp"
#include "student.hpp"
#include "enrollment.hpp"
#include "inputHandle.hpp"
#include "course.hpp"
#include "fileHandle.hpp"
#include "gpa.hpp"

//  _       __     __                             __           __  __       
// | |     / /__  / /________  ____ ___  ___     / /_____     / /_/ /_  ___ 
// | | /| / / _ \/ / ___/ __ \/ __ `__ \/ _ \   / __/ __ \   / __/ __ \/ _ \
// | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /_/ /_/ /  / /_/ / / /  __/
// |__/|__/\___/_/\___/\____/_/ /_/ /_/\___/   \__/\____/   \__/_/ /_/\___/ 
                                                                         
//    _____ __            __           __ 
//   / ___// /___  ______/ /__  ____  / /_
//   \__ \/ __/ / / / __  / _ \/ __ \/ __/
//  ___/ / /_/ /_/ / /_/ /  __/ / / / /_  
// /____/\__/\__,_/\__,_/\___/_/ /_/\__/  
                                       
//     __  ___                                                  __ 
//    /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_
//   / /|_/ / __ `/ __ \/ __ `/ __ `/ _ \/ __ `__ \/ _ \/ __ \/ __/
//  / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_  
// /_/  /_/\__,_/_/ /_/\__,_/\__, /\___/_/ /_/ /_/\___/_/ /_/\__/  
//                          /____/                                 
//    _____            __               
//   / ___/__  _______/ /____  ____ ___ 
//   \__ \/ / / / ___/ __/ _ \/ __ `__ \
//  ___/ / /_/ (__  ) /_/  __/ / / / / /
// /____/\__, /____/\__/\___/_/ /_/ /_/ 
//      /____/                          


int main(){
    bool loginStatus = false;
    int choice1, choice2, choice3;
    PasswordManager passwordManager("data/login.csv");
    Student student("data/student.csv");
    Course course("data/course.csv");
    Enrollment enrollment("data/student.csv", "data/course.csv", "data/enrollment.csv");

    while (true){
        
        system("cls");

        if (!loginStatus){    
            std::cout << std::format("{:^60}", "**Welcome to the Student Management System**") << std::endl << std::endl;
            std::cout << std::format("|{:^20}|{:^20}|{:^20}|", "[1] Register", "[2] Login", "[3] Exit") << std::endl;

            choice1 = GetUserChoice(3, "Enter your choice: ");

            if (choice1 == 1){
                system("cls");
                passwordManager.RegisterUser();
                continue;
            }

            else if (choice1 == 2){
                system("cls");
                if (passwordManager.Login())
                    loginStatus = true;
                else{
                    std::cout << "Login Failed" << std::endl;
                    continue;
                }
            }

            else if (choice1 == 3) break;
        }


        if (loginStatus){
            system("cls");

            std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Student Info", "[2] Course Info", "[3] Enrollment Info", "[4] Log Out")<< std::endl;
            choice2 = GetUserChoice(4, "Enter your choice: ");

            if (choice2 == 4) loginStatus = false;
        }

        if (loginStatus && choice2 == 1){
            while (true){
                system("cls");
                std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add", "[2] Display", "[3] Update Name", "[4] Delete", "[5] Back") << std::endl;

                choice3 = GetUserChoice(5, "Enter your choice: ");

                if (choice3 == 1) student.Add();
                else if (choice3 == 2) {
                    student.Display();
                    system("pause");
                }
                else if (choice3 == 3) student.UpdateStudentName();
                else if (choice3 == 4) student.Delete();
                else if (choice3 == 5) break;

                UpdateGPA();
            }
        }

        if (loginStatus && choice2 == 2){
            while (true){
                system("cls");
                std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add", "[2] Display", "[3] Update Name", "[4] Update Credit", "[5] Delete", "[6] Back") << std::endl;

                choice3 = GetUserChoice(6, "Enter your choice: ");

                if (choice3 == 1) course.Add();
                else if (choice3 == 2) {
                    course.Display();
                    system("pause");
                }
                else if (choice3 == 3) course.UpdateCourseName();
                else if (choice3 == 4) course.UpadateCourseCredit();
                else if (choice3 == 5) course.Delete();
                else if (choice3 == 6) break;

                UpdateGPA();
            }
        }

        if (loginStatus && choice2 == 3){
            while (true){
                system("cls");
                std::cout << std::format("|{:^20}|{:^20}|{:^20}|{:^20}|", "[1] Add", "[2] Display", "[3] Delete", "[4] Back") << std::endl;

                choice3 = GetUserChoice(4, "Enter your choice: ");

                if (choice3 == 1){
                    enrollment.Add();
                    system("pause");
                }
                else if (choice3 == 2) {
                    enrollment.Display();
                    system("pause");
                }
                else if (choice3 == 3) enrollment.Delete();
                else if (choice3 == 4) break;

                UpdateGPA();
            }
        }
    }

    return 0;
}