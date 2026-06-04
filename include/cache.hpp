#pragma once 

#include "reader.hpp"
#include <vector>




void saveCache(const std::vector<Commit> &commits , const std::string &path);

std::vector<Commit> loadCache(const std::string  &cachePath);