#pragma once
 
#include "fileHandle.hpp"

class Course : public FileHandle{
private:
    struct CourseData{
        int id;
        std::string name;
        int credit;
    };
    CourseData InputCourseData();
public:
    Course(std::string fn);
    void Add();
    void Display();
    void UpdateCourseName();
    void UpadateCourseCredit();
};