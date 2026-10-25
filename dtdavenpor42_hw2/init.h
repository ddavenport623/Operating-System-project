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

int print_progress(unsigned int row,
                   unsigned int column,
                   const char *message,
                   unsigned int percent,
                   unsigned int width);