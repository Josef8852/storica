#include <git2.h>
#include <iostream>
#include "../include/reader.hpp"


using namespace std ; 


int main(int argc , char* argv[]) {

        git_libgit2_init();

        try {
               vector<Commit> commits = readCommits(argv[1]);

               for(auto commit : commits) {
                   cout << "Name: " << commit.author.name << " message: " << commit.message << endl ;
               }
               
           } 
           catch(const exception& e) {
               cout << "error: " << e.what() << endl;
           }
        
        git_libgit2_shutdown();
        
        return 0 ; 
}