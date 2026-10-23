#pragma once

#include "pcb.h"

struct PCB_Q{
    PCB_t* head;
    PCB_t* tail;
};

typedef struct PCB_Q PCB_Q_t;

void q_enqueue(PCB_Q_t *q, PCB_t *pcb);
PCB_t *q_dequeue(PCB_Q_t *q);