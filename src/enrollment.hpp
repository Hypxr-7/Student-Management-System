#pragma once

#include "fileHandle.hpp"

class Enrollment : public FileHandle{
private:
    std::string studentFileName;
    std::string courseFileName;
public:
    Enrollment(std::string studentfn, std::string coursefn, std::string enrollmentfn);
    void Display();
    void Delete();
    void Add();
};