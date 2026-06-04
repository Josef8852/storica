#include "../include/cache.hpp"
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json ;
using namespace std ; 

void saveCache(const vector<Commit> &commits, const string &path) {
    
    ofstream file(path) ; 

    json data ; 

    for(const auto &commit : commits) {

        json commitJson = {
            {"name" , commit.author.name}, 
            {"email" , commit.author.email}, 
            {"hash",commit.hash} , 
            {"message",commit.message},
            {"timeStamp",commit.timeStamp},
            {"fileChanges" , json::array()}
        };

        for(const auto &fc : commit.fileChanges) {
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