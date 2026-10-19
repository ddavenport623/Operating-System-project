#include "pcb.h"
#include "kernel.h"
#include "ctype.h"

PCB_t *Pcb_alloc(){
    if (pcb_free_list == NULL){
        return 0;
    }
    PCB_t *val = pcb_free_list;
    pcb_free_list = pcb_free_list->pcb;
    return val;
}