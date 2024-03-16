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
    data.gpa = CalculateGPA(data.id);
    return data;
}


double Student::CalculateGPA(int id){   
    std::vector<EnrollmentData> enrollments = GetEnrollments(id);
    double totalGPA = 0;
    int totalCredit = 0;
    for (auto enrollment : enrollments){
        std::ifstream courseFile("data/course.csv");
        std::string line;
        std::getline(courseFile, line);  // skip header
        while (std::getline(courseFile, line)){
            std::stringstream ss(line);
            std::string courseID, name, credit;
            std::getline(ss, courseID, ',');
            std::getline(ss, name, ',');
            std::getline(ss, credit, ',');
            if (enrollment.courseID == std::stoi(courseID)){
                totalGPA += GradeToGPA(enrollment.grade) * std::stoi(credit);
                totalCredit += std::stoi(credit);
            }
        }
        courseFile.close();
    }

    return totalGPA / totalCredit;
}

std::vector<Student::EnrollmentData> Student::GetEnrollments(int id){
    std::ifstream enrollmentFile("data/enrollment.csv");

    std::vector<EnrollmentData> enrollments;
    std::string line;

    std::getline(enrollmentFile, line);  // skip header

    while (std::getline(enrollmentFile, line)){
        std::stringstream ss(line);
        std::string studentID, courseID, grade;
        std::getline(ss, studentID, ',');
        std::getline(ss, courseID, ',');
        std::getline(ss, grade, ',');
        if (id == std::stoi(studentID)){
            enrollments.push_back({std::stoi(studentID), std::stoi(courseID), grade});
        }
    }

    return enrollments;
}

double Student::GradeToGPA(std::string grade){
    switch (grade.c_str()[0]){
        case 'A':
            return 4.0;
        case 'B':
            return 3.0;
        case 'C':
            return 2.0;
        case 'D':
            return 1.0;
        case 'F':
            return 0.0;
        default:
            return 0.0;
    }
}

