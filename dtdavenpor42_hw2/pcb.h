#pragma once

#include <stdint.h>
#include "stack.h"
#include "ctype.h"

typedef struct PCB PCB_t;

struct PCB {
    uint64_t * sp; // Stack pointer
    uint64_t pid; // process ID
    int(*fun)(); // pointer to process' function
    Stack_t *procStack; // pointer to process' stack
    PCB_t *pcb; // pointer to PCB_t
};

PCB_t *Pcb_alloc();