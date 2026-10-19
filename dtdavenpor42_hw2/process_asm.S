// dispatch()
    @ stp x29, x30, [sp, #-16]!     /* must store these two register before call          */
    @         call save_rest_of_context     /* Save registers x0-x28 and PSTATE                   */
    @         call schedule                 /* select the next process to run                     */
    @         call  restore_context         /* restore the selected process's context (see above) */
    @     /* never get here */

// save_rest_of_context()
    @ /* stack layout:
    @         ↓Top of stack
    @         x0 x2 ... x28 PSTATE x29 x30
    @     */
    @     /* Save the context of the current process */
    @     Make room for the process context by
    @         subracting 16*15 from ps
    @     /* There are 15 pairs for x0-x28 plus PSTATE - remember 
    @         x29 and x30 are already on the stack */
    
    @     Save the process general purpose registers x0-x28
    @         /* Note that x28 is at 16*14 */ 

    @     save the process' PSTATE  
    @     /* First load the PSTATE into x0 via: mrs     x0, SPSR_EL1
    @             Then store it at sp+16*14+8
    @     */
    @     Store sp into the PCB
    @     /* How? Move sp into a register, say x0.
    @         Then load a register with the address of Running, say x1.
    @         Next, load a register with the address of the PCB (its in x1)
    @             into a register (you can reuse x1).
    @         Lastly, store sp (which is in x0) into where x1 points.
    @         Note: this requires that the first thing in your PCB is
    @                     the sp member. */
    @     ret

// restore_context()
    @ 1) read the stack pointer value out of the pcb at which Running 
    @     points and put it into the sp register. 
    @     The code should look like the following: 
    @     adr  x1, Running                 /* Running holds a pointer to the PCB of the running process */ 
    @     ldr  x0, [x1]                    /* Load PCB pointer into x0 */ 
    @     ldr  x2, [x0]                    /* x2 now has the value of the top of stack ptr (we can't ldr sp directly) */ 
    @     mov  sp, x2                      /* sp now has the top of stack for the chosen process */ 
    @ 2) restore the PSTATE stored in the stack
    @     /* note: the PSTATE is stored in the stack at 16*14+8 from the top of the stack.
    @         So, load it into x0, and then do the following: 
    @         msr  SPSR_EL1, x0 
    @ */
    @ 3) copy all register values for x0-x30 from the stack at which sp 
    @     points into those registers.
    @     /* note: x0 is at sp, x1 is at sp+8 ..., and x28 is at 16*14, 
    @     but x29 and x30 are at 16*15 (because STATE was stored at 16*14+8)
    @     use ldp when you can (you have to use ldr to load x28) to load pairs 
    @     for speed */  
    @ 4) add 16*16 to sp to pop the processor context from the stack
    @ 5) ret