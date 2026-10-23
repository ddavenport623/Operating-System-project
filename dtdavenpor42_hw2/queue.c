#include "queue.h"

void q_enqueue(PCB_Q_t *q, PCB_t *pcb){
    if (q->head == NULL){
        q->head = pcb;
        q->tail = pcb;
        return;
    }
    q->tail->pcb = pcb;
    q->tail = q->tail->pcb;
}

PCB_t *q_dequeue(PCB_Q_t *q){
    if (q->head == NULL) return NULL;
    PCB_t* retval = q->head;
    q->head = q->head->pcb;
    return retval;
}