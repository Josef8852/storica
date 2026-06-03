#pragma once

#include <cstdint>
#include <string>
#include <vector>


struct FileChange {
    std::string fileChanged ; 
    int linesAdded ; 
    int linesDeleted ; 
};

struct Author {
    std::string name ; 
    std::string email ;
};

struct Commit {
    std::string hash ; 
    Author author ; 
    std::string message ; 
    int64_t timeStamp  ;
    std::vector<FileChange> fileChanges ;
};


std::vector<Commit> readCommits(const std::string &path) ;