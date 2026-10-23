.global restore_context
.global dispatch

dispatch:
    stp x29, x30, [sp, #-16]!     /* must store these two register before call*/
    @ call save_rest_of_context     /* Save registers x0-x28 and PSTATE
    bl save_rest_of_context
    @ call schedule                 /* select the next process to run*/
    bl schedule
    @ call  restore_context         /* restore the selected process's context (see above) */
    b restore_context
    @     /* never get here */

save_rest_of_context:
    @ /* stack layout:
    @     ↓Top of stack
    @     x0 x2 ... x28 PSTATE x29 x30
    @ */
    @ /* Save the context of the current process */
    @ Make room for the process context by
    @     subracting 16*15 from ps
    sub sp, sp, #(16*15)
    @ /* There are 15 pairs for x0-x28 plus PSTATE - remember 
    @     x29 and x30 are already on the stack */
    @ Save the process general purpose registers x0-x28
    @     /* Note that x28 is at 16*14 *
    stp x0, x1, [sp, #(16*0)]
    stp x2, x3, [sp, #(16*1)]
    stp x4, x5, [sp, #(16*2)]
    stp x6, x7, [sp, #(16*3)]
    stp x8, x9, [sp, #(16*4)]
    stp x10, x11, [sp, #(16*5)]
    stp x12, x13, [sp, #(16*6)]
    stp x14, x15, [sp, #(16*7)]
    stp x16, x17, [sp, #(16*8)]
    stp x18, x19, [sp, #(16*9)]
    stp x20, x21, [sp, #(16*10)]
    stp x22, x23, [sp, #(16*11)]
    stp x24, x25, [sp, #(16*12)]
    stp x26, x27, [sp, #(16*13)]
    str x28, [sp, #(16*14)]

    @ save the process' PSTATE  
    @ /* First load the PSTATE into x0 via: mrs     x0, SPSR_EL1
    @         Then store it at sp+16*14+8
    @ */
    mrs x0, SPSR_EL1
    str x0, [sp, #(16*14+8)]
    @ Store sp into the PCB
    @ /* How? Move sp into a register, say x0.
    mov x0, sp
    @     Then load a register with the address of Running, say x1.
    adr x1, Running
    @     Next, load a register with the address of the PCB (its in x1)
    @         into a register (you can reuse x1).
    ldr x1, [x1]
    @     Lastly, store sp (which is in x0) into where x1 points.
    @     Note: this requires that the first thing in your PCB is
    @                 the sp member. */
    str x0, [x1]
    @ ret
    ret

restore_context:
    @ 1) read the stack pointer value out of the pcb at which Running 
    @     points and put it into the sp register. 
    @     The code should look like the following: 
    adr  x1, Running                 /* Running holds a pointer to the PCB of the running process */
    ldr  x0, [x1]                    /* Load PCB pointer into x0 */
    ldr  x2, [x0]                    /* x2 now has the value of the top of stack ptr (we can't ldr sp directly) */ 
    mov  sp, x2                      /* sp now has the top of stack for the chosen process */

    @ 2) restore the PSTATE stored in the stack
    @     /* note: the PSTATE is stored in the stack at 16*14+8 from the top of the stack.
    ldr x0, [sp, #(16*14+8)]
    @         So, load it into x0, and then do the following:
    msr  SPSR_EL1, x0 

    @ 3) copy all register values for x0-x30 from the stack at which sp 
    @     points into those registers.
    @     /* note: x0 is at sp, x1 is at sp+8 ..., and x28 is at 16*14, 
    @     but x29 and x30 are at 16*15 (because STATE was stored at 16*14+8)
    @     use ldp when you can (you have to use ldr to load x28) to load pairs 
    @     for speed */
    ldp x0, x1, [sp, #(16*0)]
    ldp x2, x3, [sp, #(16*1)]
    ldp x4, x5, [sp, #(16*2)]
    ldp x6, x7, [sp, #(16*3)]
    ldp x8, x9, [sp, #(16*4)]
    ldp x10, x11, [sp, #(16*5)]
    ldp x12, x13, [sp, #(16*6)]
    ldp x14, x15, [sp, #(16*7)]
    ldp x16, x17, [sp, #(16*8)]
    ldp x18, x19, [sp, #(16*9)]
    ldp x20, x21, [sp, #(16*10)]
    ldp x22, x23, [sp, #(16*11)]
    ldp x24, x25, [sp, #(16*12)]
    ldp x26, x27, [sp, #(16*13)]
    ldr x28, [sp, #(16*14)]
    ldp x29, x30, [sp, #(16*15)]

    @ 4) add 16*16 to sp to pop the processor context from the stack
    add sp, sp, #(16*16)

    @ 5) ret
    ret