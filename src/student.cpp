#include "student.hpp"

Student::Student(std::string studentFileName) : studentFileName(studentFileName) {
    std::ifstream file(studentFileName);
    assert(file.is_open());
    studentCount = 0;
    std::string line;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        studentCount++;
        lastID = stoi(StripString(line.substr(0, line.find(","))));
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

// TODO - Implement CalculateGPA
double Student::CalculateGPA(std::string name){
    double gpa;
    std::cout << "Enter GPA for " << name << ": ";
    std::cin >> gpa;
    return gpa;
}

void Student::AddStudent(){
    StudentData studentData = InputStudentData();
    std::ofstream file(studentFileName, std::ios::app);
    assert(file.is_open());
    file << studentData.id << "," << studentData.name << "," << studentData.gpa << std::endl;
    file.close();
}

void Student::DisplayStudents(){
    std::ifstream file(studentFileName);
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

    std::ifstream file(studentFileName);
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
    remove(studentFileName.c_str());
    rename("data/temp.csv", studentFileName.c_str());
}

void Student::UpdateStudentName(){
    int id = -1;
    while (id > studentCount || id < 0){
        std::cout << "Enter student ID to update: ";
        std::cin >> id;
    }

    std::string newName;
    std::cout << "Enter new name: ";
    std::cin.ignore();
    std::getline(std::cin, newName);
    while (!CheckValidName(newName)){
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, newName);
    }

    std::ifstream file(studentFileName);
    assert(file.is_open());
    std::string line;
    std::ofstream temp("data/temp.csv");
    assert(temp.is_open());
    std::getline(file, line);
    temp << line << std::endl;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string idStr, name, gpa;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, gpa, ',');
        if (std::stoi(idStr) == id)
            temp << idStr << "," << newName << "," << gpa << std::endl;
        else
            temp << line << std::endl;
    }
    file.close();
    temp.close();
    remove(studentFileName.c_str());
    rename("data/temp.csv", studentFileName.c_str());
}