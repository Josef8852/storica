#include "../include/chapters.hpp"

using namespace std ; 

vector<Chapter> detectChapters(const vector<WeekStat> &weeks) {

    vector<Chapter> chapters ; 
    
    double total  = 0 ; 

    if(weeks.empty()) return {} ;

    for(const auto &week : weeks) {
        total += week.commitsPerWeek ;
    }

    double average = total / weeks.size() ;

    double threshold = average * 2.0 ;
   
    bool inChapter = false  ; 

    Chapter currentChapter {}; 

    for(const auto &week :weeks) {
        
        if(week.commitsPerWeek > threshold && !inChapter) {
            inChapter = true ; 
            currentChapter.startDate = week.weekStart ;
            currentChapter.endDate  = week.weekStart ; 
            currentChapter.commitCount = week.commitsPerWeek ;
        }
        else if(week.commitsPerWeek > threshold && inChapter) {
            currentChapter.endDate = week.weekStart ; 
            currentChapter.commitCount += week.commitsPerWeek ;
        }
        else if(week.commitsPerWeek < threshold && inChapter) {
            chapters.push_back(currentChapter);
            inChapter = false ; 
        }

        
    }

    if (inChapter) chapters.push_back(currentChapter);

    return chapters ;
}