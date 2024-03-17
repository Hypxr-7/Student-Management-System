#pragma once

#include "fileHandle.hpp"

class Student : public FileHandle{
private:
    struct StudentData{
        int id;
        std::string name;
        double gpa;
    };
    StudentData InputStudentData();
public:
    Student(std::string studentFileName);
    void Add();
    void Display();
    void UpdateStudentName();
};