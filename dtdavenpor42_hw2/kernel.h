#pragma once

#include "pcb.h"
#include "stack.h"
#include "queue.h"

// Constants
#define _MAX_PROCESSES 10

// Global Variables
extern PCB_t * pcb_free_list;
extern PCB_t Pcbs [_MAX_PROCESSES];
extern Stack_t * Stack_free_list;
extern Stack_t Stacks[_MAX_PROCESSES];
extern PCB_Q_t* Ready_q;
extern uint64_t next_pid;
extern PCB_t* Running;