#include <git2.h>
#include <iostream>
#include "../include/reader.hpp"
#include "../include/analyzer.hpp"


using namespace std ; 


int main(int argc , char* argv[]) {

        git_libgit2_init();

        try {
               vector<Commit> commits = readCommits(argv[1]);

               vector<FileStat> stats = analyze(commits);
               

               if(string(argv[2]) == "--hot") {
                   for(int i = 0; i < 20; i++) {
                       cout << stats[i].fileName << " " << stats[i].touchCount << endl;
                   }
               }
           } 
           catch(const exception& e) {
               cout << "error: " << e.what() << endl;
           }
        
        git_libgit2_shutdown();
        
        return 0 ; 
}