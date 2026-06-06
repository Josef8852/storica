#include "../include/utils.hpp"
#include <ctime>

using namespace std ; 


string formatDate(int64_t timestamp , const string &format) {

    time_t t = timestamp;
    
    char buf[32];
    
    strftime(buf, sizeof(buf), format.c_str(), localtime(&t));
    
    return string(buf);
    
}



