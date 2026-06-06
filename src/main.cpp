#include "../include/reader.hpp"
#include "../include/analyzer.hpp"
#include "../include/tui.hpp"
#include <git2.h>
#include <iostream>
#include <filesystem>

using namespace std ; 


int main(int argc , char* argv[]) {

        if (argc < 2) { 
            cout << "usage: storica <repo>\n";
            return 1 ; 
        }

        git_libgit2_init();

        try {
               vector<Commit> commits = readCommits(argv[1]);

               vector<FileStat> stats = getCommitsStats(commits);
               
               string repoName = filesystem::path(argv[1]).filename().string();
               
               runTUI(repoName, stats);
               
           } 
           catch(const exception& e) {
               cout << "error: " << e.what() << endl;
           }
        
        git_libgit2_shutdown();
        
        return 0 ; 
}