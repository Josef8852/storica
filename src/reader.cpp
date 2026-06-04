#include "../include/reader.hpp"
#include "../include/cache.hpp"
#include <git2.h>
#include <stdexcept>

using namespace std ; 


vector<Commit> readCommits(const string &path) {

    vector<Commit> commits ; 

    git_repository *repo = nullptr ;
    
    int repo_error = git_repository_open(&repo, path.c_str()); 

    if(repo_error  < 0) {
        throw runtime_error("Failed to open repo at: " + path);
    }

    string cachePath = string(git_repository_path(repo)) + "storica_cache.json";

    vector<Commit> cached = loadCache(cachePath);

    if(!cached.empty()) {
        git_repository_free(repo);
        return cached ;
    }

    git_revwalk *walker = nullptr ; 

    int walker_error = git_revwalk_new(&walker, repo);

    git_revwalk_sorting(walker, GIT_SORT_TIME);
    
    walker_error = git_revwalk_push_head(walker); 

    if(walker_error < 0) {
         git_revwalk_free(walker); 
         throw runtime_error("Failed to access repository HEAD");
    }
    
    git_oid oid;
    while (!git_revwalk_next(&oid, walker)) {
        
        git_commit *commit = nullptr;
        int commit_error = git_commit_lookup(&commit, repo, &oid);

        if(commit_error < 0) {
             git_commit_free(commit);
             continue ; 
        }

   
        const char *message = git_commit_message(commit);
        const git_signature *author = git_commit_author(commit);
        git_time_t time = git_commit_time(commit); 

        Commit metadata = {
            git_oid_tostr_s(&oid) ,
            {author->name , author->email},
            message,
            time,
        };

    
        unsigned int count = git_commit_parentcount(commit);

        FileChange fileChange ;

        if(count == 0) {
            commits.push_back(metadata);
            git_commit_free(commit);
            continue ;
        }
        else {

              git_commit *parent = nullptr;
              int parent_error = git_commit_parent(&parent, commit, 0);

              if(parent_error < 0) {
                  git_commit_free(commit);
                  continue;
              }

              git_tree *commit_tree = nullptr;
              git_tree *parent_tree = nullptr ; 
              int commitTree_err = git_commit_tree(&commit_tree, commit);
              int parentTree_err = git_commit_tree(&parent_tree, parent);

              if(commitTree_err < 0 || parentTree_err < 0) {
                  git_tree_free(commit_tree);
                  git_tree_free(parent_tree);
                  git_commit_free(parent);
                  git_commit_free(commit);
                  continue ;
              }

    

              git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
              
              opts.flags = GIT_DIFF_SKIP_BINARY_CHECK;
              
              git_diff *diff = nullptr;
              int diff_error = git_diff_tree_to_tree(&diff, repo, parent_tree, commit_tree, &opts);

              if(diff_error < 0) {
                   git_tree_free(commit_tree);
                   git_tree_free(parent_tree);
                   git_commit_free(parent);
                   git_commit_free(commit);
                   continue;
              }


            
              size_t numDiffs =  git_diff_num_deltas(diff);

              for(size_t i = 0 ; i < numDiffs ; i++) {
              
                  const git_diff_delta *delta  = git_diff_get_delta(diff, i);

                  fileChange = {
                      delta->new_file.path, 
                      0, 
                      0,
                  };

                  metadata.fileChanges.push_back(fileChange);
              }
              
              git_diff_free(diff);
              git_tree_free(commit_tree);
              git_tree_free(parent_tree);
              git_commit_free(parent);
        }

        commits.push_back(metadata);
        git_commit_free(commit);
    }

    git_revwalk_free(walker);
    git_repository_free(repo);

    saveCache(commits, cachePath);

    return commits ;
}