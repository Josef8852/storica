#include "../include/analyzer.hpp"
#include <unordered_map>
#include <algorithm>

using namespace std ;


vector<FileStat> analyze(const vector<Commit> &commits) {
    
    vector<FileStat> stats ; 

    unordered_map<string, int> touches ; 
    
    for(const auto &commit : commits) {
        for(const auto &fc : commit.fileChanges) {
            touches[fc.fileChanged]++;
        }
    }


    for(const auto &entry : touches) {
        stats.push_back({entry.first ,entry.second , 0 , 0 , 0 ,false});
    }

    sort(stats.begin() ,stats.end() , [](const FileStat &a, const FileStat &b) -> bool {
        return a.touchCount > b.touchCount ;
    });


    return stats ; 
}
