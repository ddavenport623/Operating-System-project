#include "queue.h"

void q_enqueue(PCB_Q_t *q, PCB_t *pcb){
    if (q->head == 0){
        q->head = pcb;
        q->tail = pcb;
        return;
    }
    q->tail->pcb = pcb;
    q->tail = q->tail->pcb;
    q->tail->pcb = 0;
}

PCB_t *q_dequeue(PCB_Q_t *q){
    if (q->head == 0) return 0;
    PCB_t* retval = q->head;
    if (q->head->pcb == 0){
        q->head = 0;
        q->tail = 0;
    } else {
        q->head = q->head->pcb;
    }
    return retval;
}