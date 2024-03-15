#include "enrollment.hpp"

Enrollment::Enrollment(std::string studentfn, std::string coursefn, std::string enrollmentfn) : FileHandle(enrollmentfn){
    studentFileName = studentfn;
    courseFileName = coursefn;
}

void Enrollment::Add(){
    std::ifstream studentFile(studentFileName);
    std::ifstream courseFile(courseFileName);
    std::ofstream enrollmentFile(fileName, std::ios::app);

    std::cout << "Enter ID of student to enroll: ";
    std::string studentID;
    std::cin >> studentID;

    std::cout << "Enter ID of course to enroll student in: ";
    std::string courseID;
    std::cin >> courseID;

    std::string line;
    bool studentFound = false;
    while(std::getline(studentFile, line)){
        if(line.find(studentID) != std::string::npos){
            studentFound = true;
            break;
        }
    }
    if(!studentFound){
        std::cout << "Student not found." << std::endl;
        return;
    }

    bool courseFound = false;
    while(std::getline(courseFile, line)){
        if(line.find(courseID) != std::string::npos){
            courseFound = true;
            break;
        }
    }
    if(!courseFound){
        std::cout << "Course not found." << std::endl;
        return;
    }

    enrollmentFile << studentID << "," << courseID << "," << "N/A" << std::endl;
}

void Enrollment::Display(){
    std::ifstream enrollmentFile(fileName);
    std::string line;
    while(std::getline(enrollmentFile, line)){
        std::cout << line << std::endl;
    }
}

void Enrollment::Delete(){
    std::ifstream enrollmentFile(fileName);
    std::ofstream tempFile("temp.csv");
    std::string line;
    std::string studentID, courseID;
    std::cout << "Enter ID of student to unenroll: ";
    std::string unenrollID;
    std::cin >> unenrollID;
    while(std::getline(enrollmentFile, line)){
        std::stringstream ss(line);
        std::getline(ss, studentID, ',');
        std::getline(ss, courseID, ',');
        if(studentID != unenrollID){
            tempFile << line << std::endl;
        }
    }
    tempFile.close();
    enrollmentFile.close();
    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
}

