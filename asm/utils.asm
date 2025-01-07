.section .data

buffer: .space 81                           // 81 bytes voor de ASCII buffer 64 bits getal, plus spaties, plus afsluiter \n of spatie

.section .text

.global to_ascii                            // label moet extern bekend zijn om aan te roepen, dus .global

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

    mov w11, 4                              // voor niet-decimaal groeperen per 4
    cmp x7, 10                              // controleer of het decimaal is
    b.ne group_digits                       // Gebruik groepen van 3 voor andere decimaal
    mov w11, 3                              // Voor decimaal groep van 3

group_digits:
    udiv w12, w10, w11                      // Bereken of groep is voltooid
    msub w12, w12, w11, w10                 // Controleer of modulo 0 is
    cbnz w12, skip_space                    // Als niet gelijk aan 0, dan geen spatie

    udiv x12, x5, x7
    cbz x12, skip_space                     // Controleer of je al aan het begin zit, dan ook geen spatie

    sub x1, x1, 1                           // Verplaats bufferpointer naar links
    mov w6, ' '                             // Zet spatie in register
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

