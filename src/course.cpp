#include "course.hpp"

Course::Course(std::string fn) : FileHandle(fn) {}

Course::CourseData Course::InputCourseData(){
    CourseData data;
    data.id = ++lastID;
    data.name = StripString(GetUserInput("Enter course name: "));
    data.credit = GetUserChoice(5, "Enter course credit: ");
    return data;
}

void Course::Add(){
    CourseData data = InputCourseData();
    std::ofstream file(fileName, std::ios::app);
    assert(file.is_open());

    file << data.id << "," << data.name << "," << data.credit << std::endl;
    file.close();
}

void Course::Display(){
    std::ifstream file(fileName);
    assert(file.is_open());
    std::string line;
    std::cout << std::format("{:^5} {:^20} {:^5}\n", "ID", "Name", "Credit") << std::endl;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string id, name, credit;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, credit, ',');
        std::cout << std::format("{:^5} {:^20} {:^5}\n", id, name, credit);
    }
    file.close();
}

void Course::UpdateCourseName(){
    int id = GetUserChoice(lastID, "Enter ID to update: ");
    std::string newName = StripString(GetUserInput("Enter new course name: "));

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

void Course::UpadateCourseCredit(){
    int id = GetUserChoice(lastID, "Enter ID to update: ");
    int newCredit = GetUserChoice(5, "Enter new course credit: ");

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
            std::string oldCredit = StripString(line.substr(line.rfind(",")));
            line.replace(line.find(oldCredit), oldCredit.length(), std::to_string(newCredit));
        }
        tempFile << line << std::endl;
    }
    file.close();
    tempFile.close();
    remove(fileName.c_str());
    rename(tempFileName.c_str(), fileName.c_str());
}