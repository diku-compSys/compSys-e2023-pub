# Øvelser til 7. december

Følgende øvelser fra COD:

4.16
1)
For non-pipeline er svaret summen af de individuelle komponenter = 1250 ps
For pipeline er svaret det langsommeste af de enkelte komponenter = 350 ps

2)
lw går gennem alle komponenter, så svaret er i begge tilfælde 1250 ps.

3)
Split ID, så er den nye latenstid 300 ps.

4)
Hvor stor en andel af instruktionerne tilgår hukommelsen?
Load + store = 35%

5)
Hvor stor en andel af insturktionerne skriver til et register?
ALU/Logic + Load = 65%

4.18
x11 = 11
x12 = 22

addi x11, x12, 5    FE|DE|EX|ME|WB
add  x13, x11, x12     FE|DE|EX|ME|WB
addi x14, x11, 15         FE|DE|EX|ME|WB

Anden instruktion læser fra registrene før første register når at skrive til x11, så  x13 = 11 + 22 = 33
Tredje instruktion læser fra registrene inden de forrige instruktioner skriver til dem, så x14 = 11 + 15 = 26

4.20
WB er færdig efter første halvdel af en clock-cyklus, DE starter først efter første halvdel af en clock-cyklus. Derfor har vi:

addi x11, x12, 5    FE|DE|EX|ME|WB
NOP                   
NOP                      
add  x13, x11, x12          |FE|DE|EX|ME|WB
addi x14, x11, 15              |FE|DE|EX|ME|WB
NOP                               
add  x15, x13, x12                   |FE|DE|EX|ME|WB

4.23 
1)
En enkelt cyklus vil stadig tag 350 ps.
Generelt, hvis vi før havde cycle_time = max(FE,DE,EX,ME,WB), vil vi nu have max(FE,DE,max(EX,ME),WB)
2)

Vi har nu kun 4 trin for hver instruktion, FE, DE, EX/ME, WB, så tiden vil være FE + DE + max(EX, ME) + WB. Vi vil også opleve færre stalls hvis vi skal vente på WBs (medmindre eksemplet i næste opgave).

3)
Det tager længere tid at regne en addresse-offset ud, så hvis vi skal bruge en addresse lige efter vi har regnet den ud, så er vi nødt til at stalle.


4.31
Givet kode:

    addi x12, x0,  0   
    jal  ENT             
TOP:slli x5,  x12, 3        
    nop
    add  x6,  x10, x5       
    lw   x7,  0(x6)
    lw   x29, 8(x6)
    sub  x30, x7,  x29
    sub  x31, x11, x5
    sw   x30, 0(x31)
    addi x12, x12, 2
ENT:bne  x12, x13, TOP
TOP:slli x5,  x12, 3
    add  x6,  x10, x5
    lw   x7,  0(x6)
    lw   x29, 8(x6)
    sub  x30, x7,  x29
    sub  x31, x11, x5
    sw   x30, 0(x31)
    addi x12, x12, 2
ENT:bne  x12, x13, TOP

1)
Notation: nop hvis vi ikke kan køre efterfølgende instruktion samtidig med nuværende instruktion
>>: Der stalles i det forrige komponent, eg EX|>> betyder EX staller


    addi x12, x0,  0  |FE|DE|EX|ME|WB
    nop                
    jal  ENT             |FE|DE|EX|ME|WB
    nop
TOP:slli x5,  x12, 3        |FE|DE|EX|ME|WB
    nop
    add  x6,  x10, x5          |FE|DE|EX|ME|WB
    nop                       
    lw   x7,  0(x6)               |FE|DE|EX|ME|WB
    nop     
    lw   x29, 8(x6)                  |FE|DE|EX|ME|WB
    nop
    sub  x30, x7,  x29                  |FE|DE|EX|>>|ME|WB
    nop
    sub  x31, x11, x5                      |FE|DE|EX|>>|ME|WB
    nop
    sw   x30, 0(x31)                          |FE|DE|EX|>>|ME|WB
    addi x12, x12, 2                          |FE|DE|EX|>>|ME|WB
ENT:bne  x12, x13, TOP                           |FE|DE|EX|>>|ME|WB
    nop
TOP:slli x5,  x12, 3                                |FE|DE|EX|>>|ME|WB
    nop
    add  x6,  x10, x5                                  |FE|DE|EX|>>|ME|WB
    nop
    lw   x7,  0(x6)                                       |FE|DE|EX|>>|ME|WB
    nop
    lw   x29, 8(x6)                                          |FE|DE|EX|>>|ME|WB
    nop
    sub  x30, x7,  x29                                          |FE|DE|EX|>>|>>|ME|WB
    nop
    sub  x31, x11, x5                                              |FE|DE|EX|>>|>>|ME|WB
    nop
    sw   x30, 0(x31)                                                  |FE|DE|EX|>>|>>|ME|WB
    addi x12, x12, 2                                                  |FE|DE|EX|>>|>>|ME|WB
ENT:bne  x12, x13, TOP                                                   |FE|DE|EX|>>|>>|ME|WB


2)
2-issue CPU'en har 15 cykler per loop
Siden vi kun kan sætte instruktioner sammen et enkelt sted, har vi 16 cykler i en 1-issue.
Dette giver en speedup på 16/15 = 1.067 = 6.7%




