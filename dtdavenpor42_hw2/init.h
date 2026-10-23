#pragma once

#include "kernel.h"
#include "pcb.h"
#include "queue.h"
#include "helper.h"
#include "libos.h"

void init();
// pcb
void init_pcb_heap();
// stack
void init_stack_heap();
// queue
void q_init(PCB_Q_t *q);