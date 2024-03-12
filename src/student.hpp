#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <format>
#include <sstream>
#include <cassert>
#include "inputHandle.hpp"

class Student{
private:
    int studentCount;
    int lastID;
    std::string studentFileName;
    struct StudentData{
        int id;
        std::string name;
        double gpa;
    };
    StudentData studentData;
    StudentData InputStudentData();
    double CalculateGPA(std::string name);
public:
    Student(std::string studentFileName);
    void AddStudent();
    void DisplayStudents();
    void UpdateStudentName();
    void DeleteStudent();
};