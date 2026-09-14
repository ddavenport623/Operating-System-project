.extern strlen
.extern print_to
.extern putc_to
.global print_progress

// Notes from office hours:
// use mov instead of str for putting imediates into registers


print_progress:
    // row = w0
    // column = w1
    // address of label = x2
    // percent = w3
    // width = w4

    // Save x29 and x30
    sub sp, sp, 32
    str x29, [sp, 16]
    str x30, [sp]

    // save any registers from x19 to x28 that you may use as local variables
    sub sp, sp, 128       // Grows by 16 per register saved
    str x19, [sp, 112]
    str x20, [sp, 96]
    str x21, [sp, 80]
    str x22, [sp, 64]
    str x23, [sp, 48]
    str x24, [sp, 32]
    str x25, [sp, 16]
    str x26, [sp]

    // Save args in higher registers
    mov x22, x0           // row
    mov x23, x1           // column
    mov x24, x2           // addr of label
    mov x25, x3           // percent
    mov x26, x4           // width

    // print the message using print_to() with argument for row, column, and label address
    // Save registers x29 and x30
    bl print_to           // arguments are already in the registers for args

    cmp x25, 100          // if percent is above 100
    bgt return_with_error // then return 1  /* error, called with bad parameters */

    // calculate the the number of '=' to draw using mul and udiv  /* (percent x width)/100 */
    // /* leave answer is a register acting as a local variable, say x19 */
    mul x19, x25, x26     // percent x width
    mov x5, 100
    udiv x19, x19, x5     // above divided by 100

    // call strlen() on label address  put in a register, say x20 */
    mov x0, x24           // Should move the adr of message into arg
    bl strlen
    mov x20, x0           // Should be return length of string from strlen
    // add x23, x23, x20

    // put '=' in a local variable (say x21)
    mov x21, '='

loop:
    cmp x19, 0   // if count of equal signs (in x19) is zero or lower
    bgt continue

    mov x21, ' ' // put ' ' (space) in local variable (x21)

continue:
    // Should be the end of the loop
    cmp x26, 0      // if width is 0
    beq return_ok   // return (i.e. jump to .return_ok)

    // call putc_to to print the "=" (or the space) at column + length of label string (in x20)
    // args = row, column, char
    mov x0, x22
    mov x1, x23
    mov x2, x21
    bl putc_to

    add x23, x23, 1 // increment column by 1
    sub x19, x19, 1 // decrement count of equal signs by 1 (x19)
    sub x26, x26, 1 // decrement width by 1
    b loop

return_with_error:
    mov w0, 1
    b done

return_ok:
    mov w0, 0

done:
    // clean up stack
    ldr x26, [sp]
    ldr x25, [sp, 16]
    ldr x24, [sp, 32]
    ldr x23, [sp, 48]
    ldr x22, [sp, 64]
    ldr x21, [sp, 80]
    ldr x20, [sp, 96]
    ldr x19, [sp, 112]
    add sp, sp, 128

    ldr x30, [sp]
    ldr x29, [sp, 16]
    add sp, sp, 32
    ret