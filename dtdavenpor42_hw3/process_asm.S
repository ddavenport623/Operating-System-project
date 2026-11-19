.global restore_context
.global dispatch
.global setup_EVT
.global init_timer

dispatch:
    stp x29, x30, [sp, #-16]!     /* must store these two register before call*/
    // call save_rest_of_context     /* Save registers x0-x28 and PSTATE
    bl save_rest_of_context
    // pop  x29 and x30 off the operating system stack
    add sp, sp, #16
    // call schedule                 /* select the next process to run*/
    bl schedule
    // call  restore_context         /* restore the selected process's context (see above) */
    b restore_context
    //     /* never get here */

save_rest_of_context:
    // /* stack layout:
    //     ↓Top of stack
    //     x0 x2
    //      ... 
    //     x28 PSTATE
    //     ELR_EL1 0
    //     x29 x30
    //     PSTATE
    // */

    // save x1 Temporarily so we can use it to reference the process stack.  We will save x1 on the process stack in a moment.
    stp xzr, x1, [sp, -16]!

    // load the process stack pointer
    mrs x1, SP_EL0

    // Make room for the process context by subtracting 16*17 from x1
    sub x1, x1, #(16*17)
    
    // store x0 and x1 onto process stack (use x1 as the stack reference)
    str x0, [x1]
    ldr x0, [sp, #8] // Load x0 with the saved value of the process' x1 (its at sp + 8)
    str x0, [x1, #8] // Store x0 in the process stack at x1+8
    add sp, sp, 16 // pop process x1 off os stack - its stored already in process stack

    // /* Save the context of the current process */
    // Make room for the process context by
    //     subracting 16*15 from ps
    // sub sp, sp, #(16*15)
    // /* There are 15 pairs for x0-x28 plus PSTATE - remember 
    //     x29 and x30 are already on the stack */
    // Save the process general purpose registers x0-x28
    //     /* Note that x28 is at 16*14 *
    // stp x0, x1, [sp, #(16*0)]
    stp x2, x3, [x1, #(16*1)]
    stp x4, x5, [x1, #(16*2)]
    stp x6, x7, [x1, #(16*3)]
    stp x8, x9, [x1, #(16*4)]
    stp x10, x11, [x1, #(16*5)]
    stp x12, x13, [x1, #(16*6)]
    stp x14, x15, [x1, #(16*7)]
    stp x16, x17, [x1, #(16*8)]
    stp x18, x19, [x1, #(16*9)]
    stp x20, x21, [x1, #(16*10)]
    stp x22, x23, [x1, #(16*11)]
    stp x24, x25, [x1, #(16*12)]
    stp x26, x27, [x1, #(16*13)]
    str x28, [x1, #(16*14)]

    // Next you need to save the process' x29 and x30 to the process' stack (which x1 points to)
    // Remember, the caller put x29 and x30 on the OS stack.  So move them to the process stack.
    ldr x0, [sp] // Load process' x29 from os stack (sp points to it) into x0
    str x0, [x1, #(16*16)] // Store process x29 (now in x0) in process stack
    ldr x0, [sp, #8] // Load x0 with process' x30 from os stack
    str x0, [x1, #(16*16+8)] // Store process x30 (now in x0) in process stack

    // save the process' PSTATE  
    // /* First load the PSTATE into x0 via: mrs     x0, SPSR_EL1
    //         Then store it at sp+16*14+8
    // */
    mrs x0, SPSR_EL1
    str x0, [x1, #(16*14+8)]

    // Next, we need to save the address used to return from the interrupt handler onto
    //   the process' stack
    mrs     x0, ELR_EL1 // load x0 with the interrupt return address (in ELR_EL1)
    str     x0, [x1, #(16*15)] // store the interrupt return address in the process' stack

    //     Then load a register with the address of Running, say x1.
    adr x0, Running
    //     Next, load a register with the address of the PCB (its in x1)
    //         into a register (you can reuse x1).
    ldr x0, [x0]
    //     Lastly, store sp (which is in x0) into where x1 points.
    //     Note: this requires that the first thing in your PCB is
    //                 the sp member. */
    str x1, [x0]
    // ret
    ret

restore_context:
    // 1) read the stack pointer value out of the pcb at which Running 
    //     points and put it into the sp register. 
    //     The code should look like the following: 
    adr  x0, Running                 /* Running holds a pointer to the PCB of the running process */
    ldr  x0, [x0]                    /* Load PCB pointer into x0 */
    ldr  x1, [x0]                    /* x2 now has the value of the top of stack ptr (we can't ldr sp directly) */ 
    // mov  sp, x2                      /* sp now has the top of stack for the chosen process */

    // Next, restore the PSTATE and ELR_EL1 of the process
    ldr x0, [x1, #(16*14+8)] // Load the PSTATE from x1+16*14+8 into x0
    msr SPSR_EL1, x0
    ldr x0, [x1, #(16*15)] // Load ELR_EL1 from x1+16*15 into x0
    msr ELR_EL1, x0

    // Next, store the new top of stack into the system exception register.
    mov x0, x1 // Put x1 into x0 and add 16*17 to x0 (make a clean stack)
    add x0, x0, #(16*17)
    msr SP_EL0, x0 //   When the handler returns via eret, this will be the value of sp for the process

    // restore process context
    // Use ldp to load x2-x28 from the process stack  // x2,x3 is at x1+16, etc.
    ldp x2, x3, [x1, #(16*1)]
    ldp x4, x5, [x1, #(16*2)]
    ldp x6, x7, [x1, #(16*3)]
    ldp x8, x9, [x1, #(16*4)]
    ldp x10, x11, [x1, #(16*5)]
    ldp x12, x13, [x1, #(16*6)]
    ldp x14, x15, [x1, #(16*7)]
    ldp x16, x17, [x1, #(16*8)]
    ldp x18, x19, [x1, #(16*9)]
    ldp x20, x21, [x1, #(16*10)]
    ldp x22, x23, [x1, #(16*11)]
    ldp x24, x25, [x1, #(16*12)]
    ldp x26, x27, [x1, #(16*13)]
    ldr x28, [x1, #(16*14)] // Load x28 from x1+16*14

    // Call clear_timer(), but store x0,x1 onto OS stack before and restore them after
    sub sp, sp, 16
    stp x0, x1, [sp]
    bl clear_timer
    ldp x0, x1, [sp]
    add sp, sp, 16

    ldp x29, x30, [x1, #(16*16)] // Load x29 and x30 from x1+16*16
    ldp x0, x1, [x1] // Load x0 and x1 from x1+0
    msr     DAIFClr, #0x2       // Clear IRQ disable flag
    eret

setup_EVT:
	// set up the exception vector table
    adr     x0, vector_table 
    msr     VBAR_EL1, x0        // Set the vector base address
    ret

init_timer:
    stp     x29, x30, [sp, -16]!
    bl      clear_timer
    //route core 0 counter to core 0 irq
    ldr     x0, =0x40000040
    mov     x1, 0x08
    str     w1, [x0]
    // enable timer
    mov     x0, 1
    msr     CNTV_CTL_EL0, x0
    ldp     x29, x30, [sp], 16
    ret

clear_timer:
    // read count frequency
    mrs     x0, CNTFRQ_EL0
    mov     x1, 20
    udiv    x0, x0, x1
    // clear cntv interrupt and set next 1 sec timer.
    msr     CNTV_TVAL_EL0, x0
    ret

.balign 2048
vector_table:
    .balign 128
        b unsupported
    .balign 128
        b dispatch
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b dispatch    // yes
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b dispatch
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b unsupported
    .balign 128
        b dispatch
    .balign 128
        b unsupported
    .balign 128
        b unsupported