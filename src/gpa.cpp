#include "gpa.hpp"

double CalculateGPA(int id){   
    std::vector<EnrollmentData> enrollments = GetEnrollments(id);
    double totalGPA = 0;
    int totalCredit = 0;
    for (auto enrollment : enrollments){
        std::ifstream courseFile("data/course.csv");
        std::string line;
        std::getline(courseFile, line);  // skip header
        while (std::getline(courseFile, line)){
            std::stringstream ss(line);
            std::string courseID, name, credit;
            std::getline(ss, courseID, ',');
            std::getline(ss, name, ',');
            std::getline(ss, credit, ',');
            if (enrollment.courseID == std::stoi(courseID)){
                totalGPA += GradeToGPA(enrollment.grade) * std::stoi(credit);
                totalCredit += std::stoi(credit);
            }
        }
        courseFile.close();
    }

    return totalGPA / totalCredit;
}

std::vector<EnrollmentData> GetEnrollments(int id){
    std::ifstream enrollmentFile("data/enrollment.csv");

    std::vector<EnrollmentData> enrollments;
    std::string line;

    std::getline(enrollmentFile, line);  // skip header

    while (std::getline(enrollmentFile, line)){
        std::stringstream ss(line);
        std::string studentID, courseID, grade;
        std::getline(ss, studentID, ',');
        std::getline(ss, courseID, ',');
        std::getline(ss, grade, ',');
        if (id == std::stoi(studentID)){
            enrollments.push_back({std::stoi(studentID), std::stoi(courseID), grade});
        }
    }

    return enrollments;
}

double GradeToGPA(std::string grade){
    switch (grade.c_str()[0]){
        case 'A':
            return 4.0;
        case 'B':
            return 3.0;
        case 'C':
            return 2.0;
        case 'D':
            return 1.0;
        case 'F':
            return 0.0;
        default:
            return 0.0;
    }
}


std::vector<int> GetStudentID(){
    std::ifstream enrollmentFile("data/enrollment.csv");
    std::vector<int> studentID;
    std::string line;
    std::getline(enrollmentFile, line);  // skip header
    while (std::getline(enrollmentFile, line)){
        std::stringstream ss(line);
        std::string studentIDStr, courseID, grade;
        std::getline(ss, studentIDStr, ',');
        std::getline(ss, courseID, ',');
        std::getline(ss, grade, ',');
        int id = std::stoi(studentIDStr);
        studentID.push_back(id);
    }
    enrollmentFile.close();
    return studentID;
}

void UpdateGPA(){
    std::vector<int> studentID = GetStudentID();
    std::fstream tempfile("data/temp.csv", std::ios::out);
    std::ifstream studentFile("data/student.csv");
    std::string line;
    std::getline(studentFile, line);  // skip header
    for (int id : studentID){
        double gpa = CalculateGPA(id);
        std::getline(studentFile, line);
        std::stringstream ss(line);
        std::string studentID, name;
        std::getline(ss, studentID, ',');
        std::getline(ss, name, ',');
        tempfile << studentID << "," << name << "," << gpa << std::endl;
    }

    studentFile.close();
    tempfile.close();
    std::remove("data/student.csv");
    std::rename("data/temp.csv", "data/student.csv");
}