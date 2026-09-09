.extern strlen
.global print_progress

print_progress:
    ; row = w0
    ; column = w1
    ; address of label = x2
    ; percent = w3
    ; width = w4

    ; Save x29 and x30
    sub sp, sp, 32
    str x29, [sp + 16]
    str x30, [sp]

    ; save any registers from x19 to x28 that you may use as local variables
    sub sp, sp, 48 ; Grows by 16 per register saved
    str x19, [sp + 32]
    str x20, [sp + 16]
    str x21, [sp]

    ; print the message using print_to() with argument for row, column, and label address
    ; Save registers x29 and x30
    sub sp, sp, 32
    str x29, [sp + 16]
    str x30, [sp]
    bl print_to ; arguments are already in the registers for args
    str sp, x30
    str [sp + 16], x29 ; Might need to be load instead of store
    add sp, sp, 32

    cmp w4, 100           ; if percent is above 100
    bgt return_with_error ; then return 1  /* error, called with bad parameters */

    ; calculate the the number of '=' to draw using mul and udiv  /* (percent x width)/100 */
    ; /* leave answer is a register acting as a local variable, say x19 */
    mul x19, w3, w4    ; percent x width
    udiv x19, x19, 100 ; above divided by 100

    ; call strlen() on label address  put in a register, say x20 */
    ; put '=' in a local variable (say x21)

.loop
    cmp x19, 0      ; if count of equal signs (in x19) is zero
    bl add_space    ; put ' ' (space) in local variable (x21)

    ; Should be the end of the loop
    cmp w4, 0       ; if width is 0
    beq return_ok   ; return (i.e. jump to .return_ok)

    ; call putc_to to print the "=" (or the space) at column + length of label string (in x20)

    add w1, w1, 1   ; increment column by 1
    sub x19, x19, 1 ; decrement count of equal signs by 1 (x19)
    sub w4, w4, 1   ; decrement width by 1
    b loop

.add_space: ; put ' ' (space) in local variable (x21)
    str ' ', x21 ; Highly doubt this is correct but I'll fix it later
    ret

.return_with_error:
    mov w0, 1
    b done

.return_ok:
    mov w0, 0

.done:
    ; clean up stack
    ret