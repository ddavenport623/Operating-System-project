
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
    sub sp, sp, 48
    ; save x19
    str x19, [sp + 32]
    ; save x20
    str x20, [sp + 16]
    ; save x21
    str x21, [sp]

    ; print the message using print_to() with argument for row, column, and label address

    ; if percent is above 100 then return 1  /* error, called with bad parameters */

    ; calculate the the number of '=' to draw using mul and udiv  /* (percent x width)/100 */
    ; /* leave answer is a register acting as a local variable, say x19 */

    ; call strlen() on label address  put in a register, say x20 */
    ; put '=' in a local variable (say x21)

    ; loop
        ; if count of equal signs (in x19) is zero
            ; put ' ' (space) in local variable (x21)

        ; if width is 0
            ; return (i.e. jump to .return_ok)

        ; call putc_to to print the "=" (or the space) at column + length of label string (in x20)

        ; increment column by 1
        sub w1, w1, 1
        ; decrement count of equal signs by 1 (x19)
        ; decrement width by 1
        sub w4, w4, 1
    ; end loop

.return_with_error:
    mov w0, 1
    b done

.return_ok:
    mov w0, 0

.done:
    ; clean up stack
    ret