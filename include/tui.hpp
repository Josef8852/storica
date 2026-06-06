#pragma once

#include "analyzer.hpp"
#include "chapters.hpp"
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>


ftxui::Element renderHeader(const std::string &repoName, bool showChapters);


void runTUI(
    const std::string &repoName, 
    const std::vector<FileStat> &stats , 
    const std::vector<Chapter> &chapters);