// #include "file.hpp"

// int main(){
//     File file("data/", "student.csv");
//     // file.temp_displayAttributes();
//     file.DisplayFile();
//     file.AddToFile("John Doe");
//     file.DisplayFile();
//     file.DeleteFromFile(1);
//     file.DisplayFile();

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

// Function to split a string by delimiter
std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Function to read CSV file and output content in a table
void readCSV(const std::string& filename, char delimiter) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read and output header
    if (std::getline(file, line)) {
        std::vector<std::string> headers = splitString(line, delimiter);
        for (const auto& header : headers) {
            std::cout << std::setw(15) << std::left << "| " << header << " ";
        }
        std::cout << "|" << std::endl;

        // Output table separator
        for (size_t i = 0; i < headers.size(); ++i) {
            std::cout << "+";
            for (size_t j = 0; j < 17; ++j) {
                std::cout << "-";
            }
        }
        std::cout << "+" << std::endl;
    }

    // Read and output data
    while (std::getline(file, line)) {
        std::vector<std::string> values = splitString(line, delimiter);
        for (const auto& value : values) {
            std::cout << std::setw(15) << std::left << "| " << value << " ";
        }
        std::cout << "|" << std::endl;
    }

    file.close();
}

int main() {
    std::string filename = "data.csv"; // Provide your CSV file name here
    char delimiter = ','; // Specify the delimiter used in the CSV file
    
    readCSV(filename, delimiter);

    return 0;
}
