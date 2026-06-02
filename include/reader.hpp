#pragma once

#include <cstdint>
#include <string>
#include <vector>

using namespace  std;

struct FileChange {
    string fileChanged ; 
    int linesAdded ; 
    int linesDeleted ; 
};

struct Commit {
    string hash ; 
    string author ; 
    string message ; 
    int64_t timeStamp  ;
    vector<FileChange> fileChanges ;
};


vector<Commit> getCommits(const string &path) ;