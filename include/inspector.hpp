#pragma once

#include "reader.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct FileStory {
    std::string fileName ;
    int64_t bornDate ; 
    int64_t lastTouched ; 
    int commitCount;
    std::vector<std::pair<std::string, int>> topContributers ; 
};


FileStory inspectFile(const std::vector<Commit> &commits ,const std::string &fileName);