#pragma once

#include <vector>
#include "fileHandle.hpp"

class Student : public FileHandle{
private:
    struct StudentData{
        int id;
        std::string name;
        double gpa;
    };
    struct EnrollmentData{
        int studentID;
        int courseID;
        std::string grade;
    };
    StudentData InputStudentData();
    double GradeToGPA(std::string grade);
    std::vector<EnrollmentData> GetEnrollments(int id);
    double CalculateGPA(int id);
public:
    Student(std::string studentFileName);
    void Add();
    void Display();
    void UpdateStudentName();
};