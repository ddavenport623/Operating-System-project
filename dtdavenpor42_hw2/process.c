#include "process.h"
// spawn_process()
int spawn_process(int (*code_address) ()){
    // set stackobj to return value of calling Stack_alloc() to allocate a stack

    // check to make sure stackobj is not null
		// (if it is, return -1)
    
    // set stackptr to stackobj->stack 

    // Set up the stack. sp is a uint64_t *
    // set sp to stackptr + _STACK_SIZE to put sp at the bottom of the stack    
        // Note that if stackptr is a pointer to a uint64_t, then stackptr+1024 will point to the right place
   
    /* initialze the stack with the starting context for the process
        to look like: 
                        ↓top of stack
                        x0  x1  x2  x3 ... x28  PSTATE  x29  x30
                        0   0   0   0      0    0       0    code_address                
    */ 

    // create context that will set gen purpose regs to 0
    // loop i from 0 to 32 (inclusive)
    //     decrement sp  // sp should be a pointer to a uint64_t
    //     set the uint64_t at which sp points to 0

    // set the value at which sp+31 points to code_address 
        // Note: type cast code_address to a uint64_t so that the compiler does not complain)
        // Note: you will have to declare pcb to be of type PCB_t for the following code

    //     set pcb to the return value of Pcb_alloc() to allocate a pcb for the process
	// check the pcb and if is null then return -1
    //     set the pcb's sp member to sp.
    //     set the pcb's pid member to next_pid  //Note that you can keep track
    //                                           // of the next pid using a
    //                                           // global variable         
    //     set the corresponding members in the pcb to the function and address 
    //        of stack structure 
    //     enqueue the pcb (it pointer) onto the Ready_q  // Ready_q should be a global

    return 0; /* no errors occured */
        // Note that if Stack_alloc() or Pcb_alloc() returns NULL, you should return 
        //  -1 instead to indicate the error
}

// schedule()

void ready_to_run(){
    // set Running to the return value from dequeuing from Ready_q
    // Note: You should put some error code here that
    //       checked if you are dequeuing from a 
    //       empty queue
}