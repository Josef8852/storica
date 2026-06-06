#include "../include/analyzer.hpp"
#include <cstdint>
#include <unordered_map>
#include <algorithm>

using namespace std ;


vector<FileStat> getCommitsStats(const vector<Commit> &commits) {
    
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


vector<WeekStat> getWeeksStats(const std::vector<Commit> &commits) {
    
    vector<WeekStat> weeksStats ; 

    unordered_map<int64_t, int> weeks ; 

    for(const auto &commit : commits) {

        int64_t weekKey = (commit.timeStamp / SECONDS_PER_WEEK) * SECONDS_PER_WEEK  ; 

        weeks[weekKey]++;
    }

    for(const auto &week : weeks) {
        weeksStats.push_back({week.first , week.second});
    }


    sort(weeksStats.begin() ,weeksStats.end() , [] (const WeekStat &a , const WeekStat &b) -> bool {
        return a.weekStart < b.weekStart ; 
    });

    return weeksStats ;
}
