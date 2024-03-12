#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <format>
#include <sstream>
#include <cassert>

class Student{
private:
    int studentCount;
    int lastID;
    struct StudentData{
        int id;
        std::string name;
        double gpa;
    };
    StudentData studentData;
    StudentData InputStudentData();
    double CalculateGPA(std::string name);
    bool CheckValidName(std::string name);
    bool CheckValidID(int id);
    std::string StripString(std::string str);
public:
    Student();
    void AddStudent();
    void DisplayStudents();
    void UpdateStudentName();
    void DeleteStudent();
};