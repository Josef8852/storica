#include "../include/chapters.hpp"
#include "utils.hpp"

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


    if (chapters.empty()) {
        Chapter whole;
        whole.startDate = weeks.front().weekStart;
        whole.endDate = weeks.back().weekStart;
        whole.commitCount = (int)total;
        whole.name = "The whole story";
        chapters.push_back(whole);
        return chapters;
    }

    size_t maxIdx = 0 ;
   
   for(size_t i = 0 ; i < chapters.size(); i++) {
           if (chapters[i].commitCount > chapters[maxIdx].commitCount) maxIdx = i;
   }
  
   for (size_t i = 0; i < chapters.size(); i++) {
       if (i == 0){
            chapters[i].name = "The beginning";
       }
       else if (i == maxIdx) {
            chapters[i].name = "Major rewrite";
       }
       else{
            chapters[i].name = "active " + formatDate(chapters[i].startDate, "%Y");
       }
   } 

    return chapters ;
}