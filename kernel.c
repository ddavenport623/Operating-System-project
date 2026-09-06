#include "ctype.h"
#include "stdbool.h"
#include "libos.a"

// ARM functions
int print_progress(unsigned int row,
                   unsigned int column,
                   const char *message,
                   unsigned int percent,
                   unsigned int width);

int main() {
    boot_win();
    while (true){
        for(int perc = 10; perc <= 100; perc += 10){
            print_progress(19, 4, "Progress: ", perc, 10); // row, column, message, percent, width
            wait_msec(500000);
        }
    }
    return 0;
}

void boot_win() {

}

int strlen(const char *s){

}