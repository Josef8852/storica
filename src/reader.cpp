#include "../include/reader.hpp"
#include <git2.h>
#include <stdexcept>

using namespace std ; 


vector<Commit> readCommits(const string &path) {

    vector<Commit> commits ; 

    git_repository *repo = nullptr ;
    
    int repo_error = git_repository_open(&repo, path.c_str()); // == 0 success , < 0 failed

    if(repo_error  < 0) {
        throw runtime_error("Failed to open repo at: " + path);
    }

    git_revwalk *walker = nullptr ; // pointer to commit objects

    int walker_error = git_revwalk_new(&walker, repo);

    git_revwalk_sorting(walker, GIT_SORT_TIME); // sort by timestamp
    
    walker_error = git_revwalk_push_head(walker); // point to repo head

    if(walker_error < 0) {
         git_revwalk_free(walker); // free memory
         throw runtime_error("Failed to access repository HEAD");
    }
    
    git_oid oid;
    while (!git_revwalk_next(&oid, walker)) {
        git_commit *commit;
        int commit_error = git_commit_lookup(&commit, repo, &oid);

        if(commit_error < 0) {
             git_commit_free(commit);
             throw runtime_error("Failed to get current commit");
        }

        // commit metadata
        const char *message = git_commit_message(commit);
        const git_signature *author = git_commit_author(commit);
        git_time_t time = git_commit_time(commit); 

        Commit metadata = {
            git_oid_tostr_s(&oid) ,
            {author->name , author->email},
            message,
            time,
        };

        
    }


    return commits ;
}