#include "../include/cache.hpp"
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json ;
using namespace std ; 

void saveCache(vector<Commit> commits, const string &path) {
    
    std::ofstream file(path) ; 

    json data ; 

    for(auto commit : commits) {

        json commitJson = {
            {"name" , commit.author.name}, 
            {"email" , commit.author.email}, 
            {"hash",commit.hash} , 
            {"message",commit.message},
            {"timeStamp",commit.timeStamp},
            {"fileChanges" , json::array()}
        };

        for(auto fc : commit.fileChanges) {
            commitJson["fileChanges"].push_back({
                {"fileChanged" , fc.fileChanged},
                {"linesAdded" , fc.linesAdded},
                {"linesDeleted" , fc.linesDeleted}
            });
        }

        data["commits"].push_back(commitJson);
     
    }

    file << data ;
    
};