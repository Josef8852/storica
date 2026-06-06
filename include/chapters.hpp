#pragma once 

#include "analyzer.hpp"
#include <cstdint>
#include <vector>
#include <string>


struct Chapter {
    std::int64_t startDate ; 
    std::int64_t endDate ; 
    int commitCount ; 
    std::string name ; 
};



std::vector<Chapter> detectChapters(const std::vector<WeekStat> &weeks);