#include "init.h"

// all initialization functions

void init(){
    uart_init();
    lfb_init();
    boot_win();

    // Console
    print_progress(19, 33, "Console: ", 100, 10); // Console 100%
    waitSec(1);
    print_to(13, 34, "OK]"); // Change to [OK] Console

    // Memory
    print_progress(19, 33, "Memory:  ", 0, 10); // Memory 0%
    waitSec(1);
    init_pcb_heap();
    print_progress(19, 33, "Memory:  ", 50, 10); // Memory 50%
    waitSec(1);
    init_stack_heap();
    print_progress(19, 33, "Memory:  ", 100, 10); // Memory 100%
    waitSec(1);
    print_to(14, 34, "OK]"); // Change to [OK] Memory
    
    // Kernel
    print_progress(19, 33, "Kernel:  ", 0, 10); // Kernel 0%
    waitSec(1);
    q_init(&Ready_q); // Need to write
    print_progress(19, 33, "Kernel:  ", 100, 10); // Kernel 100%
    waitSec(1);
    print_to(15, 34, "OK]"); // Change to [OK] Memory

    return;
}

void init_pcb_heap(){
    for (int i=0; i < _MAX_PROCESSES - 1; i++){
        Pcbs[i].pcb = &Pcbs[i+1];
    }
    Pcbs[_MAX_PROCESSES - 1].pcb = 0;

    pcb_free_list = &Pcbs[0];
}

void init_stack_heap(){
    for (int i=0; i < _MAX_PROCESSES - 1; i++){
        Stacks[i].next = &Stacks[i+1];
    }
    Stacks[_MAX_PROCESSES - 1].next = 0;

    Stack_free_list = &Stacks[0];
}
