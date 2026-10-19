#include "pcb.h"

// Constants
#define _MAX_PROCESSES 10
#define _STACK_SIZE 1024

// Global Variables
char message[11] = "Progress: ";
PCB_t * pcb_free_list;
PCB_t Pcbs [_MAX_PROCESSES];