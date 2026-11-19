#include "init.h"

void setup_EVT();
void init_timer();
void clear_timer();

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
    q_init(&Ready_q);
    print_progress(19, 33, "Kernel:  ", 100, 10); // Kernel 100%
    waitSec(1);
    print_to(15, 34, "OK]"); // Change to [OK] Memory

    // Interrupts
    print_progress(19, 33, "Interrupts:  ", 0, 10); // Interrupts 0%
    waitSec(1);
    setup_EVT();
    print_progress(19, 33, "Interrupts:  ", 50, 10); // Interrupts 50%
    waitSec(1);
    init_timer();
    print_progress(19, 33, "Interrupts:  ", 100, 10); // Interrupts 100%
    waitSec(1);
    print_to(16, 34, "OK]"); // Change to [OK] Interrupts

    print_progress(19, 33, "Processes:  ", 0, 10); // Processes 0%
    waitSec(1);
    int retval = spawn_process(p1);
    if (!isZero(retval)){
        while (true) {}
    }
    print_progress(19, 33, "Processes:  ", 25, 10); // Processes 25%
    waitSec(1);
    retval = spawn_process(p2);
    if (!isZero(retval)){
        while (true) {}
    }
    print_progress(19, 33, "Processes:  ", 50, 10); // Processes 50%
    waitSec(1);
    retval = spawn_process(p3);
    if (!isZero(retval)){
        while (true) {}
    }
    print_progress(19, 33, "Processes:  ", 75, 10); // Processes 75%
    waitSec(1);
    retval = spawn_process(p4);
    if (!isZero(retval)){
        while (true) {}
    }
    print_progress(19, 33, "Processes:  ", 100, 10); // Processes 100%
    waitSec(1);
    print_to(17, 34, "OK]"); // Change to [OK] Processes

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
