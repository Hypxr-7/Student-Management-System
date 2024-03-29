#include "file.hpp"

int main(){
    File file("data/", "student.csv");
    // file.temp_displayAttributes();
    file.DisplayFile();
    file.AddToFile("John Doe");
    file.DisplayFile();
    file.DeleteFromFile(1);
    file.DisplayFile();

    return 0;
}