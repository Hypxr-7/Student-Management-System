#include "student.hpp"

Student::Student(std::string studentFileName) : FileHandle(studentFileName) {}

void Student::Add(){
    StudentData student = InputStudentData();
    std::ofstream file(fileName, std::ios::app);
    assert(file.is_open());
    file << student.id << "," << student.name << "," << student.gpa << std::endl;
    file.close();
}

void Student::Display(){
    std::ifstream file(fileName);
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

void Student::UpdateStudentName(){
    int id = GetUserChoice(lastID, "Enter ID to update: ");
    std::string newName = StripString(GetUserInput("Enter new student name: "));

    std::string tempFileName = fileName + ".tmp";
    std::ifstream file(fileName);
    assert(file.is_open());
    std::ofstream tempFile(tempFileName);
    assert(tempFile.is_open());

    std::string line;
    std::getline(file, line);
    tempFile << line << std::endl;
    while (std::getline(file, line)){
        if (stoi(StripString(line.substr(0, line.find(",")))) == id){
            std::string oldName = StripString(line.substr(line.find(",") + 1, line.rfind(",")));
            line.replace(line.find(oldName), oldName.length(), newName);
        }
        tempFile << line << std::endl;
    }
    file.close();
    tempFile.close();
    remove(fileName.c_str());
    rename(tempFileName.c_str(), fileName.c_str());
}

Student::StudentData Student::InputStudentData(){
    StudentData data;
    data.id = ++lastID;
    data.name = StripString(GetUserInput("Enter student name: "));
    data.gpa = CalculateGPA(data.name);
    return data;
}

double Student::CalculateGPA(std::string name){
    std::ifstream file("grades.txt");
    assert(file.is_open());
    std::string line;
    std::getline(file, line);  // skip header
    double total = 0;
    int count = 0;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string studentName, courseName, grade;
        std::getline(ss, studentName, ',');
        std::getline(ss, courseName, ',');
        std::getline(ss, grade, ',');
        if (studentName == name){
            total += std::stod(grade);
            count++;
        }
    }
    file.close();
    return total / count;
}

