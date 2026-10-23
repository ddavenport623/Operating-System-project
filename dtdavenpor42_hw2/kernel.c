#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"

#include "libos.h"
#include "helper.c"
#include "init.h"
#include "stack.h"
#include "kernel.h"
#include "process.h"
#include "queue.h"

PCB_t * pcb_free_list;
PCB_t Pcbs [_MAX_PROCESSES];
Stack_t * Stack_free_list;
Stack_t Stacks[_MAX_PROCESSES];
PCB_Q_t Ready_q;
uint64_t next_pid = 0;
PCB_t* Running;

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
        return -1;
    }
    retval = spawn_process(p2);
    if (!isZero(retval)){
        return -1;
    }
    retval = spawn_process(p3);
    if (!isZero(retval)){
        return -1;
    }
    retval = spawn_process(p4);
    if (!isZero(retval)){
        return -1;
    }

    ready_to_run();
    restore_context();
}

void boot_win() {
    print_to(11, 30, "+------------------------------------------------------+\n");
    print_to(12, 30, "|                                                      |\n");
    print_to(13, 30, "|  [-]  Console                                        |\n");
    print_to(14, 30, "|  [-]  Memory                                         |\n");
    print_to(15, 30, "|  [-]  Kernel                                         |\n");
    print_to(16, 30, "|  [-]  Interrupts                                     |\n");
    print_to(17, 30, "|  [-]  Processes                                      |\n");
    print_to(18, 30, "|                                                      |\n");
    print_to(19, 30, "|  Progress:                                           |\n");
    print_to(20, 30, "|                                                      |\n");
    print_to(21, 30, "+------------------------------------------------------+\n");
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
    // print the message "Process 1: " at row 11, three spaces left of the boot_win() box
    print_to(11, 1, "Process 1: ");
    // loop infinitely
    while (true){
        // loop i from 0 to 9
        for (int i=0; i <= 9; i++){
            // use putc_to to print the character i immediately after the ": " in the above message 
            // convert i to a character by adding ' ' (a spaced) to it: i + ' '
            putc_to(11, 12, i + '0');
            // call dispatch()
            dispatch();
        }
    }
}

int p2(){
    // The same for p1, but print "Process 2: 0"
    // and the message should be printed 2 rows
    // below p1's output.

    // print the message "Process 2: " at row 13, three spaces left of the boot_win() box
    print_to(13, 1, "Process 2: ");
    // loop infinitely
    while (true){
        // loop i from 0 to 9
        for (int i=0; i <= 9; i++){
            // use putc_to to print the character i immediately after the ": " in the above message 
            // convert i to a character by adding ' ' (a spaced) to it: i + ' '
            putc_to(13, 12, i + '0');
            // call dispatch()
            dispatch();
        }
    }
}

int p3(){
    // Now create two more functions for p3 and p4, but begin
    // printing at column that is 10 columns after p1's (and p2's)
    // output. See the video for how the running OS should look.

    // print the message "Process 3: " at row 13, three spaces left of the boot_win() box
    print_to(11, 16, "Process 3: ");
    // loop infinitely
    while (true){
        // loop i from 0 to 9
        for (int i=0; i <= 9; i++){
            // use putc_to to print the character i immediately after the ": " in the above message 
            // convert i to a character by adding ' ' (a spaced) to it: i + ' '
            putc_to(11, 27, i + '0');
            // call dispatch()
            dispatch();
        }
    }
}

int p4(){
    // Now create two more functions for p3 and p4, but begin
    // printing at column that is 10 columns after p1's (and p2's)
    // output. See the video for how the running OS should look.

    // print the message "Process 4: " at row 13, three spaces left of the boot_win() box
    print_to(13, 16, "Process 4: ");
    // loop infinitely
    while (true){
        // loop i from 0 to 9
        for (int i=0; i <= 9; i++){
            // use putc_to to print the character i immediately after the ": " in the above message 
            // convert i to a character by adding ' ' (a spaced) to it: i + ' '
            putc_to(13, 27, i + '0');
            // call dispatch()
            dispatch();
        }
    }
}