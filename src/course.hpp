#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <format>
#include <sstream>
#include <cassert>  
#include "inputHandle.hpp"

class Course{
private:
    int courseCount;
    int lastID;
    std::string courseFileName;
    struct CourseData{
        int id;
        std::string name;
        int credit;
    };
    CourseData courseData;
    CourseData InputCourseData();
public:
    Course(std::string fn);
    void AddCourse();
    void DisplayCourses();
    void UpdateCourseName();
    void UpadateCourseCredit();
    void DeleteCourse();
};