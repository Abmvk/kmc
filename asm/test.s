.section .data

message:    .asciz "De waarde van register x0 is: "
newline:    .asciz "\n"
buffer:     .space 11

.section .text
.global _start

_start:
    // De som, uitkomst parkeren in x3
    mov x1, 10
    mov x2, 20
    add x3, x1, x2

    // Schrijf de tekst naar stdout
    ldr x1, =message
    mov x2, 29
    mov x8, 64
    mov x0, 1
    svc 0

    // converteer de waarde van x3 naar ASCII
    ldr x1, =buffer
    mov x4, x3
    mov x10, 10

convert_to_ascii:
    udiv x5, x4, x10
    msub x6, x5, x10, x4
    add x6, x6, 48
    strb w6, [x1], 1
    mov x4, x5
    cmp x4, 0
    bne convert_to_ascii

    mov w6, '\n'
    strb w6, [x1], 1

    sub x2, x1, buffer

    // schrijf de buffer naar stdout
    ldr x1, =buffer
    mov x8, 64
    mov x0, 1
    svc 0

    //en afsluiten
    mov x8, 93
    mov x0, 0
    svc 0

