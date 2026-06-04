#include "../include/cache.hpp"
#include <cstdint>
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


vector<Commit> loadCache(const std::string &cachePath) {

    vector<Commit> commits ; 

    ifstream file(cachePath) ; 
    if(!file.is_open()) {
        return {} ;
    }

    try {
         json data = json::parse(file);
         for(const auto &commitJson : data["commits"]) {
             Commit commit ; 
             commit.author.name = commitJson["name"].get<string>();
             commit.author.email = commitJson["email"].get<string>();
             commit.hash = commitJson["hash"].get<string>();
             commit.message = commitJson["message"].get<string>();
             commit.timeStamp = commitJson["timeStamp"].get<int64_t>();


             for(const auto &fc : commitJson["fileChanges"]) {
                 commit.fileChanges.push_back({
                    fc["fileChanged"], 
                    fc["linesAdded"],
                    fc["linesDeleted"]
                 });
             }
             
             commits.push_back(commit);
         }
    }
    catch(...) {}
    



    return commits ; 
}
