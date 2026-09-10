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
    print_to(0, 0, "+------------------------------------------------------+\n");
    printf(1, 0, "|                                                      |\n");
    printf(2, 0, "|  [OK] Console                                        |\n");
    printf(3, 0, "|  [-]  Memory                                         |\n");
    printf(4, 0, "|  [-]  Kernel                                         |\n");
    printf(5, 0, "|  [-]  Interrupts                                     |\n");
    printf(6, 0, "|  [-]  Processes                                      |\n");
    printf(7, 0, "|                                                      |\n");
    printf(8, 0, "|  Progress:                                           |\n");
    printf(9, 0, "|                                                      |\n");
    printf(10, 0, "+------------------------------------------------------+\n");
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