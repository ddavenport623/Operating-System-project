#include "helper.h"
#include "libos.h"


// Converts seconds to microseconds
void waitSec(int sec){
    wait_msec(sec * 1000000);
}

// Checks if num is zero
bool isZero(int num){
    if (num == 0){
        return true;
    }
    return false;
}
