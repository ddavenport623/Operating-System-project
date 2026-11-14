#pragma once

#include "stack.h"
#include "pcb.h"
#include "queue.h"
#include "kernel.h"

int spawn_process(int (*code_address) ());
void schedule();
void ready_to_run();