#include "pcb.h"

struct PCB_Q_t{
    struct PCB* head;
    struct PCB* tail;
};

void q_init(struct PCB_Q_t *q);
void q_enqueue(struct PCB_Q_t *q, PCB_t *pcb);
PCB_t *q_dequeue(struct PCB_Q_t *q);