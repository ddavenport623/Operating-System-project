#include "ctype.h"
#include "stdbool.h"
#include "stdio.h"
#include "libos.h"
#include "libos.a"
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
int spawn_process(int (*pfun) ());
void ready_to_run();
void q_init(Queue_t *);

// Constants
#define _MAX_PROCESSES 10

// Global Variables
char message[11] = "Progress: ";
PCB_t * pcb_free_list;
PCB_t pcbs [_MAX_PROCESSES];
// STOPPED HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

void init(){
    boot_win();

    // Console
    print_progress(); // Console 0%
    waitSec(1);
    uart_init(); // CONFIRM LIBRARY WORKS
    print_progress(); // Console 50%
    waitSec(1);
    lfb_init(); // CONFIRM LIBRARY WORKS
    print_progress(); // Console 100%
    waitSec(1);
    // Change to [OK] Console

    // Memory
    print_progress(); // Memory 0%
    waitSec(1);
    init_pcb_heap(); // NEED TO WRITE
    print_progress(); // Memory 50%
    waitSec(1);
    init_stack_heap(); // NEED TO WRITE
    print_progress(); // Memory 100%
    // Change to [OK] Memory
    
    // Kernel
    print_progress(); // Kernel 0%
    waitSec(1);
    q_init(Ready_q); // Need to write
    print_progress(); // Kernel 100%
    waitSec(1);

    return;
}

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