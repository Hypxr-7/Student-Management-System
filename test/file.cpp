#include "file.hpp"

File::File(std::string path_, std::string fileName_) : path(path_), fileName(fileName_){
    std::ifstream file(path + fileName);

    assert(file.is_open()); // Check if file is open

    IDCounter = 0;

    std::string line;
    std::getline(file, line); 
    std::stringstream ss(line);
    while (!ss.eof()){
        std::string temp;
        std::getline(ss, temp, ','); // split the line by commas
        headers.push_back(temp);     // add the split to the headers
    }

    while(std::getline(file, line)){
        IDCounter++;
        lastID = std::stoi(line.substr(0, line.find(","))); // Get the ID of the last line
    }

    file.close();
} 

void File::AddToFile(std::string text){
    std::ofstream file(path + fileName, std::ios::app);
    assert(file.is_open()); // Check if file is open

    file << ++lastID << "," << text << std::endl;
    IDCounter++;

    file.close();
}

void File::DisplayFile(){
    std::ifstream file(path + fileName);
    assert(file.is_open()); // Check if file is open

    std::string line;
    std::getline(file, line); 
    for (auto header : headers){
        std::cout << std::setw(15) << header;
    }
    std::cout << std::endl;

    std::cout << std::string(15 * (headers.size() + 1), '-') << std::endl;

    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string temp;
        while (std::getline(ss, temp, ',')){
            std::cout << std::setw(15) << temp;
        }
        std::cout <<  std::endl;
    }

    file.close();

}

void File::DeleteFromFile(int ID){
    std::ifstream file(path + fileName);
    assert(file.is_open()); // Check if file is open

    std::ofstream tempFile(path + "temp.csv");
    assert(tempFile.is_open()); // Check if file is open

    std::string line;
    std::getline(file, line);
    tempFile << line << std::endl;

    while (std::getline(file, line)){
        if (std::stoi(line.substr(0, line.find(","))) != ID){
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();
    remove((path + fileName).c_str());
    rename((path + "temp.csv").c_str(), (path + fileName).c_str());
}