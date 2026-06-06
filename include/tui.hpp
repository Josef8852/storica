#pragma once

#include "analyzer.hpp"
#include "chapters.hpp"
#include <string>
#include <vector>

void runTUI(
    const std::string &repoName, 
    const std::vector<FileStat> &stats , 
    const std::vector<Chapter> &chapters);