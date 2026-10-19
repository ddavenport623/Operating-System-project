#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"

#include "libos.h"
#include "libos.a"
#include "helper.c"
#include "init.h"
#include "stack.h"
#include "kernel.h"
#include "process.h"

// ARM functions
int print_progress(unsigned int row,
                   unsigned int column,
                   const char *message,
                   unsigned int percent,
                   unsigned int width);

// Function prototypes
void boot_win();
int strlen(const char *);
void ready_to_run();
int p1();
int p2();
int p3();
int p4();

int main(){
    init();

    int retval = spawn_process(p1);
    if (!isZero(retval)){
        // err
    }
    retval = spawn_process(p2);
    if (!isZero(retval)){
        // err
    }
    retval = spawn_process(p3);
    if (!isZero(retval)){
        // err
    }
    retval = spawn_process(p4);
    if (!isZero(retval)){
        // err
    }

    ready_to_run();
    restore_context();
}

void boot_win() {
    print_to(11, 1, "+------------------------------------------------------+\n");
    print_to(12, 1, "|                                                      |\n");
    print_to(13, 1, "|  [-]  Console                                        |\n");
    print_to(14, 1, "|  [-]  Memory                                         |\n");
    print_to(15, 1, "|  [-]  Kernel                                         |\n");
    print_to(16, 1, "|  [-]  Interrupts                                     |\n");
    print_to(17, 1, "|  [-]  Processes                                      |\n");
    print_to(18, 1, "|                                                      |\n");
    print_to(19, 1, "|  Progress:                                           |\n");
    print_to(20, 1, "|                                                      |\n");
    print_to(21, 1, "+------------------------------------------------------+\n");
}

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

int p1(){
    // begin
    //   print the message "Process 1: " at row 11, 
    //        three spaces left of the boot_win() box
    //   loop infinitely
    //     loop i from 0 to 9
    //        use putc_to to print the character i 
    //           immediately after the ": " in the 
    //           above message 
    //        /* convert i to a character by adding
    //           ' ' (a spaced) to it: i + ' '      */
    //        call dispatch()
    //     end
    //   end  
    // end
}

int p2(){
    // The same for p1, but print "Process 2: 0"
    // and the message should be printed 2 rows
    // below p1's output.
}

int p3(){
    // Now create two more functions for p3 and p4, but begin
    // printing at column that is 10 columns after p1's (and p2's)
    // output. See the video for how the running OS should look.
}

int p4(){
    // Now create two more functions for p3 and p4, but begin
    // printing at column that is 10 columns after p1's (and p2's)
    // output. See the video for how the running OS should look.
}