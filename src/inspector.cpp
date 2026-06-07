#include "../include/inspector.hpp"
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std ; 


FileStory inspectFile(const vector<Commit> &commits, const string &fileName){

    FileStory story ; 

    story.fileName = fileName ; 

    story.commitCount = 0 ; 

    story.lastTouched = 0 ; 

    story.bornDate = INT64_MAX ;


    unordered_map<string, int> contributers ; 

    for(const auto &commit : commits ) {


        for(const auto &fc : commit.fileChanges) {
            
            if(fc.fileChanged == story.fileName) {
                story.commitCount++;
                if (commit.timeStamp < story.bornDate) {
                      story.bornDate = commit.timeStamp;
                }
                if (commit.timeStamp > story.lastTouched){
                      story.lastTouched = commit.timeStamp;
                }
                   contributers[commit.author.name]++;
                   break; 
            }
            
        }
    }

          vector<pair<string, int>> topContributers ; 

          for(const auto &entry : contributers) {
              topContributers.push_back(make_pair(entry.first, entry.second));
          }

          sort(topContributers.begin() , topContributers.end() , 
          [](const pair<string,int> &a , const pair<string,int> &b)-> bool {
              return a.second > b.second ;
          });


          story.topContributers = topContributers;

    return story ; 
}