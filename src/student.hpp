#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cassert>

class Student{
private:
    int studentCount;
    struct StudentData{
        int id;
        std::string name;
        double gpa;
    };
    StudentData studentData;
    StudentData InputStudentData();
    double CalculateGPA(std::string name);
    bool CheckValidName(std::string name);
public:
    Student();
    void AddStudent();
    void DisplayStudents();
    void UpdateStudent();
    void DeleteStudent();
};