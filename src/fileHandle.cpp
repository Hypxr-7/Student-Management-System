#include "fileHandle.hpp"

FileHandle::FileHandle(std::string fn) : fileName(fn) {
    std::ifstream file(fileName);
    assert(file.is_open());

    IDcount = 0;
    std::string line;
    std::getline(file, line);  // skip header
    while (std::getline(file, line)){
        IDcount++;
        lastID = stoi(StripString(line.substr(0, line.find(","))));
    }
    file.close();
}

void FileHandle::Delete(){
    int id = GetUserChoice(lastID, "Enter ID to delete: ");

    std::string tempFileName = fileName + ".tmp";
    std::ifstream file(fileName);
    assert(file.is_open());
    std::ofstream tempFile(tempFileName);
    assert(tempFile.is_open());

    std::string line;
    std::getline(file, line);
    tempFile << line << std::endl;
    while (std::getline(file, line)){
        if (stoi(StripString(line.substr(0, line.find(",")))) == id) continue;
        tempFile << line << std::endl;
    }
    file.close();
    tempFile.close();
    remove(fileName.c_str());
    rename(tempFileName.c_str(), fileName.c_str());
}
