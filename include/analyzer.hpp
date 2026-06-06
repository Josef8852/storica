#pragma once 

#include "reader.hpp"
#include <cstdint>
#include <string>
#include <vector>

struct FileStat {
    std::string fileName ; 
    int touchCount ; 
    int linesAdded ; 
    int linesDeleted ; 
    int64_t bornDate ; 
    bool isDeleted ;
};

struct WeekStat {
    int64_t weekStart;
    int commitsPerWeek;
};

constexpr int64_t SECONDS_PER_WEEK = 604800;


std::vector<FileStat> getCommitsStats(const std::vector<Commit> &commits);

std::vector<WeekStat> getWeeksStats(const std::vector<Commit> &commits) ; 