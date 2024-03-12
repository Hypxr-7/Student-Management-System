#include "course.hpp"

Course::Course(std::string fn) : courseFileName(fn) {
    std::ifstream file(courseFileName);
    assert(file.is_open());
    courseCount = 0;
    std::string line;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        courseCount++;
        lastID = stoi(StripString(line.substr(0, line.find(","))));
    }
    file.close();   
}

Course::CourseData Course::InputCourseData(){
    CourseData courseData;

    courseData.id = ++courseCount;

    std::cout << "Enter course Name: ";
    std::getline(std::cin, courseData.name);
    while (!CheckValidName(courseData.name)){
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, courseData.name);
    }

    std::cout << "Enter course credit: ";
    courseData.credit = GetUserChoice(10, "Enter credit (1-10): ");

    return courseData;
}

void Course::AddCourse(){
    CourseData courseData = InputCourseData();
    std::ofstream file(courseFileName, std::ios::app);
    assert(file.is_open());
    file << courseData.id << "," << courseData.name << "," << courseData.credit << std::endl;
    file.close();
}

void Course::DisplayCourses(){
    std::ifstream file(courseFileName);
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
    std::ifstream file(courseFileName);
    assert(file.is_open());
    std::string line;
    std::getline(file, line);  // skip header
    file.close();

    int id = GetUserChoice(lastID, "Enter course ID to update: ");
    std::string newName;
    std::cout << "Enter new course name: ";
    std::getline(std::cin, newName);
    while (!CheckValidName(newName)){
        std::cout << "Invalid name. Please enter a valid name: ";
        std::getline(std::cin, newName);
    }

    std::ifstream fileIn(courseFileName);
    assert(fileIn.is_open());
    std::ofstream fileOut("temp.csv");
    assert(fileOut.is_open());
    std::getline(fileIn, line);
    fileOut << line << std::endl;
    while (std::getline(fileIn, line)){
        std::stringstream ss(line);
        std::string idStr, name, credit;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, credit, ',');
        if (std::stoi(idStr) == id)
            fileOut << idStr << "," << newName << "," << credit << std::endl;
        else
            fileOut << line << std::endl;
    }
    fileIn.close();
    fileOut.close();
    std::remove(courseFileName.c_str());
    std::rename("temp.csv", courseFileName.c_str());
}

void Course::UpadateCourseCredit(){
    std::ifstream file(courseFileName);
    assert(file.is_open());
    std::string line;
    std::getline(file, line);  // skip header
    file.close();

    int id = GetUserChoice(lastID, "Enter course ID to update: ");
    int newCredit = GetUserChoice(10, "Enter new credit (1-10): ");

    std::ifstream fileIn(courseFileName);
    assert(fileIn.is_open());
    std::ofstream fileOut("temp.csv");
    assert(fileOut.is_open());
    std::getline(fileIn, line);
    fileOut << line << std::endl;
    while (std::getline(fileIn, line)){
        std::stringstream ss(line);
        std::string idStr, name, credit;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, credit, ',');
        if (std::stoi(idStr) == id)
            fileOut << idStr << "," << name << "," << newCredit << std::endl;
        else
            fileOut << line << std::endl;
    }
    fileIn.close();
    fileOut.close();
    std::remove(courseFileName.c_str());
    std::rename("temp.csv", courseFileName.c_str());
}