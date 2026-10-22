#include "init.h"

// all initialization functions

void init(){
    boot_win();

    // Console
    print_progress(19, 4, "Console: ", 0, 10);  // Console 0%
    waitSec(1);
    uart_init(); // CONFIRM LIBRARY WORKS
    print_progress(19, 4, "Console: ", 50, 10); // Console 50%
    waitSec(1);
    lfb_init(); // CONFIRM LIBRARY WORKS
    print_progress(19, 4, "Console: ", 100, 10); // Console 100%
    waitSec(1);
    print_to(13, 5, "OK"); // Change to [OK] Console

    // Memory
    print_progress(19, 4, "Memory: ", 0, 10); // Memory 0%
    waitSec(1);
    init_pcb_heap();
    print_progress(19, 4, "Memory: ", 50, 10); // Memory 50%
    waitSec(1);
    init_stack_heap();
    print_progress(19, 4, "Memory: ", 100, 10); // Memory 100%
    print_to(14, 5, "OK"); // Change to [OK] Memory
    
    // Kernel
    print_progress(19, 4, "Kernel: ", 0, 10); // Kernel 0%
    waitSec(1);
    q_init(&Ready_q); // Need to write
    print_progress(19, 4, "Kernel: ", 100, 10); // Kernel 100%
    waitSec(1);

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

    pcb_free_list = &Stacks[0];
}

void q_init(PCB_Q_t *q){
    q->head = 0;
    q->tail = 0;
}