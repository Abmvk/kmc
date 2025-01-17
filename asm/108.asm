.section .data
buffer: .space 81                           // 65 bytes voor de ASCII buffer 64 bits getal, plus spaties, plus afsluiter \n of spatie
newline: .ascii "\n"

.section .text
.global _start

_start:
    // 1. initialiseer operanden
//  mov x3, 10                              // gebruik dit voor decimale waarden tot 65.535

    movz x3, 0xFFFF, lsl 0                  // Operand 1, laagste word (x3)
    movk x3, 0xEEEE, lsl 16                 // volgende word
    movk x3, 0xDDDD, lsl 32                 // derde word
    movk x3, 0xCCCC, lsl 48                 // linker word

    mov x4, 0                               // Operand 2 (x4)

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

    // Subroutine voor ASCII-conversie
to_ascii:
    // veilig stellen x5 op de stack
    sub sp, sp, 16                          // maak ruimte op de stack voor 1 register, 16 bytes = 2 x 64 bits = eenheid ARM stack
    str x5, [sp]                            // Bewaar x5 op de stack

    ldr x1, =buffer                         // Laad bufferadres in x1
    add x1, x1, 80                          // Zet bufferpointer naar einde van de buffer
    strb w9, [x1]                           // Voeg afsluitend teken toe (x9 is in hoofdprogramma gevuld)
    sub x1, x1, 1                           // Verplaats bufferpointer naar links
    mov x2, 2                               // Stringlengte is nu 2, vanwege afsluitend teken, en de nummering van het eerste cijfer
    mov w10, 0                              // teller voor aantal geschreven cijfers

to_ascii_loop:
    udiv x6, x5, x7                         // x6 = x5 / x7, dus resultaat 1 positie naar rechts verschoven in gekozen talstelsel
    msub x6, x6, x7, x5                     // x6 = x5 - (x6 * x7), de rest die uit de verschuiving naar rechts overbleef
    cmp x6, 9                               // Als x6 groter is dan 9 moet naar een letter A-F worden omgezet
    add x6, x6, '0'                         // Zet rest om naar ASCII door '0' op te tellen
    b.le store_digit                        // Als x6 <= 9, sla op
    add x6, x6, 'A'-'0'-10                  // Corrigeer voor A-F

store_digit:
    sub x1, x1, 1                           // verplaats bufferpointer naar links
    strb w6, [x1]                           // Sla ASCII-karakter op in buffer
    add x2, x2, 1                           // Verhoog stringlengte
    add w10, w10, 1                         // Verhoog teller voor aantal geschreven karakters

    mov w11, 4                              // voor decimaal groeperen per 3
    cmp x7, 10                              // controleer of het decimaal is
    b.ne group_digits                       // Gebruik groepen van 4 voor andere talstelsels
    mov w11, 3                              // Voor niet-decimaal groep van 4

group_digits:
    udiv w12, w10, w11                      // Bereken of groep is voltooid
    msub w12, w12, w11, w10                 // Controleer of modulo 0 is
    cbnz w12, skip_space                    // Als niet gelijk aan 0, dan geen spatie

    udiv x12, x5, x7
    cbz x12, skip_space                         // Controleer of je al aan het begin zit
//    b.eq skip_space

    sub x1, x1, 1                           // Verplaats bufferpointer naar links
    mov w6, ' '                             // Xet spatie in register
    strb w6, [x1]                           // Sla spatie op in buffer
    add x2, x2, 1                           // Verhoog stringlengte

skip_space:
    udiv x5, x5, x7                         // Update x5 door naar rechts te schuiven
    cbnz x5, to_ascii_loop                  // Herhaal zolang x5 niet nul is

    mov x0, 1                               // File descriptor stdout
    mov x8, 64                              // Syscall write
    svc 0                                   // Syscall

    ldr x5, [sp]                            // Haal x5 van de stack
    add sp, sp, 16

    ret                                     // keer terug naar hoofdprogramma

