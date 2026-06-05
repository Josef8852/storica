#pragma once 

#include "reader.hpp"
#include <cstdint>
#include <string>

struct FileStat {
    std::string fileName ; 
    int touchCount ; 
    int linesAdded ; 
    int linesDeleted ; 
    int64_t bornDate ; 
    bool isDeleted ;
};


std::vector<FileStat> analyze(const std::vector<Commit> &commits);