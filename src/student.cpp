#include "student.hpp"

Student::Student(){
    std::ifstream file("data/studentList.csv");
    assert(file.is_open());
    studentCount = -1;
    std::string line;
    while (std::getline(file, line)){
        studentCount++;
    }
    file.close();
}

Student::StudentData Student::InputStudentData(){
    StudentData studentData;

    studentData.id = ++studentCount;

    std::cout << "Enter student Name: ";
    std::getline(std::cin, studentData.name);
    while (!CheckValidName(studentData.name)){
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, studentData.name);
    }

    studentData.gpa = CalculateGPA(studentData.name);

    return studentData;
}

bool Student::CheckValidName(std::string name){
    for (char c : name)
        if (!isalpha(c) && c != ' ')
            return false;
    return true;
}

// temporary function
double Student::CalculateGPA(std::string name){
    double gpa;
    std::cout << "Enter GPA for " << name << ": ";
    std::cin >> gpa;
    return gpa;
}

void Student::AddStudent(){
    StudentData studentData = InputStudentData();
    std::ofstream file("data/studentList.csv", std::ios::app);
    assert(file.is_open());
    file << studentData.id << "," << studentData.name << "," << studentData.gpa << std::endl;
    file.close();
}