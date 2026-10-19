#include "init.h"
#include "helper.c"
#include "kernel.h"

// all initialization functions

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

void init_pcb_heap(){
    // Create a linked list of PCBs from the Pcb array
    // Each element should be the addr of one of the PCBs in the array
}

void init_stack_heap(){
    // Similar to pcb version
}