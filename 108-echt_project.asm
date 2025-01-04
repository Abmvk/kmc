.section .data
buffer: .space 21                           // 21 bytes voor de ASCII buffer

.section .text
.global _start

_start:
    // 1. initialiseer operanden
    mov x3, 1234                              // Operand 1 (x3)
    mov x4, 2345                              // Operand 2 (x4)

    // 2. Bereken de som
    add x5, x3, x4                          // x5 = x3 + x4 (Resultaat)

    // 3. Zet bufferpointer naar einde van buffer
    ldr x1, =buffer                         // Laad bufferadres in x1
    add x1, x1, 20                          // Zet x1 naar het einde van de buffer
    mov w6, '\n'                            // Sluit het getal af met een newline
    strb w6, [x1]

    // 4. Zet het resultaat om naar ASCII (achterwaarts vullen)
    mov x2, 1                               // x2 houdt de lengte van de string bij, 1 aangezien we al een newline toevoegen
    mov x7, 10                              // Talstelsel = 10

to_ascii:
    udiv x6, x5, x7                         // x6 = x5 / x7 (Quotient), resultaat schuift 1 plaats naar rechts in x6
    msub x6, x6, x7, x5                     // x6 = x5 - (x6 * x7) (Rest), laatste cijfer van resultaat
    add x6, x6, '0'                         // Zet rest om naar ASCII ('0' = 48)
    sub x1, x1, 1                           // Verplaats bufferpointer naar links
    strb w6, [x1]                           // Sla ASCII-karakter op in buffer
    add x2, x2, 1                           // Verhoog stringlengte
    udiv x5, x5, x7                         // x5 = x5 / x7, resultaat schuift nu definitief 1 plaats naar rechts
    cbnz x5, to_ascii                       // herhaal zolang qutient niet 0 is

    // 5. Schrijf naar stdout
    mov x0, 1                               // File descriptor (stdout)
    mov x8, 64                              // System call nummer voor write
    svc 0                                   // System call

    // 6. Sluit programma af
    mov x0, 0                               // Exit code (0 = succesvol)
    mov x8, 93                              // System call nummer voor exit
    svc 0                                   // System call

