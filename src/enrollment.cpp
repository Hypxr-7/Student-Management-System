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
    std::getline(enrollmentFile, line); // skip header
    std::cout << std::format("{:^20} {:^20} {:^20}\n", "Student ID", "Course ID", "Grade") << std::endl;

    while(std::getline(enrollmentFile, line)){
        std::stringstream ss(line);
        std::string studentID, courseID, grade;
        std::getline(ss, studentID, ',');
        std::getline(ss, courseID, ',');
        std::getline(ss, grade, ',');
        std::cout << std::format("{:^20} {:^20} {:^20}\n", studentID, courseID, grade);
    }
    enrollmentFile.close();
}

void Enrollment::Delete(){
    std::ifstream enrollmentFile(fileName);
    std::ofstream tempFile("temp.csv");
    std::string line;
    std::string studentID, courseID;

    std::cout << "Enter ID of student to unenroll: ";
    std::string unenrollID;
    std::cin >> unenrollID;

    std::cout << "Enter ID of course to unenroll student from: ";
    std::string unenrollCourseID;
    std::cin >> unenrollCourseID;

    std::string lineToDelete = unenrollID + "," + unenrollCourseID;
    
    while(std::getline(enrollmentFile, line)){
        if(line.find(lineToDelete) == std::string::npos){
            tempFile << line << std::endl;
        }
    }
    
    tempFile.close();
    enrollmentFile.close();
    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());
}

