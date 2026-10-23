#pragma once

#include "stack.h"

int spawn_process(int (*code_address) ());
void schedule();
void ready_to_run();