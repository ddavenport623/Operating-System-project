#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"
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

void boot_win() { // Progress line may be wrong but part of that is from the example being incorrect
    printf("+------------------------------------------------------+\n");
    printf("|                                                      |\n");
    printf("|  [OK] Console                                        |\n");
    printf("|  [-]  Memory                                         |\n");
    printf("|  [-]  Kernel                                         |\n");
    printf("|  [-]  Interrupts                                     |\n");
    printf("|  [-]  Processes                                      |\n");
    printf("|                                                      |\n");
    printf("|  Progress:                                           |\n");
    printf("|                                                      |\n");
    printf("+------------------------------------------------------+\n");
}

int strlen(const char *s){

}