#include "pcb.h"
#include "kernel.h"

PCB_t *Pcb_alloc(){
    if (pcb_free_list == 0){
        return 0;
    }
    PCB_t *val = pcb_free_list;
    pcb_free_list = pcb_free_list->pcb;
    return val;
}