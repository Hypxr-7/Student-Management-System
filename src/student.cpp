#include "student.hpp"

Student::Student(){
    std::ifstream file("data/studentList.csv");
    assert(file.is_open());
    studentCount = 0;
    std::string line;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        studentCount++;
        lastID = stoi(StripString(line.substr(0, line.find(","))));
    }
    std::cout << studentCount << " students found" << std::endl;
    std::cout << "Last ID: " << lastID << std::endl;
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

// TODO - Implement CalculateGPA
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

void Student::DisplayStudents(){
    std::ifstream file("data/studentList.csv");
    assert(file.is_open());
    std::string line;
    std::cout << std::format("{:^5} {:^20} {:^5}\n", "ID", "Name", "GPA") << std::endl;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string id, name, gpa;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, gpa, ',');
        std::cout << std::format("{:^5} {:^20} {:^5}\n", id, name, gpa);
    }
    file.close();
}

void Student::DeleteStudent(){
    int id = -1;
    while (!CheckValidID(id)){
        std::cout << "Enter student ID to delete: ";
        std::cin >> id;
    }

    std::ifstream file("data/studentList.csv");
    assert(file.is_open());
    std::string line;
    std::ofstream temp("data/temp.csv");
    assert(temp.is_open());
    std::getline(file, line);
    temp << line << std::endl;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string idStr;
        std::getline(ss, idStr, ',');
        if (std::stoi(idStr) != id)
            temp << line << std::endl;
    }
    file.close();
    temp.close();
    remove("data/studentList.csv");
    rename("data/temp.csv", "data/studentList.csv");
}

bool Student::CheckValidID(int id){
    if (id < 0 || id > studentCount)
        return false;
    return true;
}

std::string Student::StripString(std::string str){
    std::string newStr;
    for (char c : str)
        if (c != ' ')
            newStr += c;
    return str;
}