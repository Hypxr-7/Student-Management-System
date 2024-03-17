#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct EnrollmentData{
    int studentID;
    int courseID;
    std::string grade;
};

double GradeToGPA(std::string grade);
std::vector<EnrollmentData> GetEnrollments(int id);
double CalculateGPA(int id);
std::vector<int> GetStudentID();
void UpdateGPA();