#include <git2.h>
#include "../include/reader.hpp"


using namespace std ; 


int main(int argc , char* argv[]) {

        git_libgit2_init();

        

        git_libgit2_shutdown();
        return 0 ; 
}