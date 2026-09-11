#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"
#include "libos.h"

// ARM functions
int print_progress(unsigned int row,
                   unsigned int column,
                   const char *message,
                   unsigned int percent,
                   unsigned int width);

void boot_win();
int strlen(const char *);

// finished but untested
int main() {
    boot_win();
    while (true){
        for(int perc = 10; perc <= 100; perc += 10){
            print_progress(19, 4, "Progress: ", perc, 10); // row, column, message, percent, width
            wait_msec(500000); // Waits half a second
        }
    }
    return 0;
}

// Finished but untested
// NOTES:
// Progress line may be wrong but part of that is from the example being incorrect
void boot_win() {
    print_to(11, 1, "+------------------------------------------------------+\n");
    print_to(12, 1, "|                                                      |\n");
    print_to(13, 1, "|  [OK] Console                                        |\n");
    print_to(14, 1, "|  [-]  Memory                                         |\n");
    print_to(15, 1, "|  [-]  Kernel                                         |\n");
    print_to(16, 1, "|  [-]  Interrupts                                     |\n");
    print_to(17, 1, "|  [-]  Processes                                      |\n");
    print_to(18, 1, "|                                                      |\n");
    print_to(19, 1, "|  Progress:                                           |\n");
    print_to(20, 1, "|                                                      |\n");
    print_to(21, 1, "+------------------------------------------------------+\n");
}

// finished but untested
int strlen(const char *s){
    if(s == NULL){ // Invalid string
        return -1;
    }
    
    int len = 0;

    while (s[len] != '\0'){
        len++;
    }

    return len;
}