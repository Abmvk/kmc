.section .data

newline: .ascii "\n"

.section .text

.global _start

_start:
    // 1. initialiseer operanden
    mov x3, 20                              // gebruik dit voor decimale waarden tot 65.535

//    movz x3, 0xFFFF, lsl 0                  // Operand 1, laagste word (x3)
//    movk x3, 0xEEEE, lsl 16                 // volgende word
//    movk x3, 0xDDDD, lsl 32                 // derde word
//    movk x3, 0xCCCC, lsl 48                 // linker word

    mov x4, 10                              // Operand 2 (x4)

//  movz x4, 0x0000, lsl 0                  // gebruik voor 64 bits waarde, rechter word
//  movk x4, 0x1111, lsl 16                 // volgende word
//  movk x4, 0x2222, lsl 32                 // derde word
//  movk x4, 0x3333, lsl 48                 // linker word

    // 2. Bereken de som
    add x5, x3, x4                          // x5 = x3 + x4 (Resultaat)

    // 3. Kies afsluitend teken
    mov w9, '\n'                            // newline als afluitend teken, kan ook spatie zijn, of komma, of punt

    //4. Roep de ASCII-print subroutine viermaal aan
    mov x7, 10                              // Talstelsel decimaal
    bl to_ascii                             // Roep printroutine aan

    mov x7, 16                              // hexadecimaal
    bl to_ascii                             // Roep printroutine aan

    mov x7, 8                               // octaal
    bl to_ascii                             // roep printroutine aan

    mov x7, 2                               // binair
    bl to_ascii                             // roep printroutine aan

    // 6. Sluit programma af
    mov x0, 1                               // Afsluiten met een newline voor nette output, naar stdout
    ldr x1, =newline                        // pointer naar de newline string
    mov x2, 1                               // newline is 1 byte
    mov x8, 64                              // Syscall write
    svc 0                                   // Syscall

    mov x0, 0                               // Exitcode (0= succesvol)
    mov x8, 93                              // Syscall exit
    svc 0                                   // Syscall
