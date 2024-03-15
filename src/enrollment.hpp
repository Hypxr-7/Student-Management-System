#pragma once

#include "fileHandle.hpp"

class Enrollment : public FileHandle{
private:
    std::string studentFileName;
    std::string courseFileName;
public:
    Enrollment(std::string studentFileName, std::string courseFileName, std::string enrollmentFileName);

};