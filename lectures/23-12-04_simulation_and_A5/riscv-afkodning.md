# Afkodning af RISC-V instruktioner

RISC-V binære maskinsprog er designet således at afkodning kan ske i to
niveauer, primær og sekundær. I COD er den primære afkoder mærket
"Control" og den sekundære "ALU Control" på figur 4.21

Den primære afkodning inddrager udelukkende "opcode" feltet
i instruktionerne og kan derfra generere alle de mest tidskritiske
styresignaler.

Den sekundære afkodning inddrager flere bits fra instruktionen,
nemlig felterne funct7 og funct3 og kan generere signaler der er
mindre tidskritiske.

Afkodningen er hierarkisk - dvs den primære afkoder producerer
nogle signaler som styrer sekundær afkodning. Mærket "ALUOp" på
figur 4.21

## Styring af ALUen

ALUen styres via de fire ALU Control Input linier. Funktionen af
Den sekundære afkoder / ALU Control er beskrevet i figur 4.12

Ideen er at værdierne 00 og 01 for ALUOp direkte styrer ALU Control
signalerne. Hvis ALUOp derimod har værdien 10 skal den sekundære
afkoder generere ALU Control Input ud fra funct3 og funct7.

Samlet bliver ALU Control Input en funktion af 12 bit, hvoraf
de 2 udtrykker styring fra den primære afkoder og de 10 andre
kommer fra instruktionen.

## Beregning af et signal

Hvordan beregnes styresignalerne fra ALU Control? Betragt som eksempel bit
2 i ALU Control Input (fra appendix A kendt som B-Negate) ?

Den nemmeste fremgangsmåde når man har en sandhedstabel er
at opskrive hver output bit som en produkt-sum, det vil sige
en OR af en eller flere AND termer.

Der skal bruges en AND term for hver række der giver 1.
For bit 2 i ALU Control Input er der to rækker i fig 4.13 der giver 1:
(Fig 4.13 er lavet fra fig 4.12 ved at udelade tekstfelter og
opstille inputs bit for bit.)

~~~
ALUUOp funct7   funct3  output (B-Negate)
01     xxxxxxx  xxx     1
10     0100000  000     1
~~~

output kan skrives som OR(and1,and2), hvor
and1 skal blive høj når ALUOp == 01
and2 skal blive høj når ALUOp == 10 og funct7 == 0100000 og funct3 == 000

Hvis vi lader X_n angive bit n i X kan vi skrive and1 og and2 således:

~~~
and1 = !ALUop_1 * ALUop_2

and2 = ALUop1 * !ALUop2 * !funct_6 * funct7_5 * !funct7_4 * !funct7_3 *
       !funct7_2 * !funct7_1 * !funct7_0 * !funct3_2 * !funct3_1 * !funct3_0

her er ! == not
og * == and
~~~

Metoden bruges på samme måde for hvert enkelt bit i output for sig.


## Den primære afkoder "Control"

Funktionaliteten af "Control" for CODs lille subset af RISC-V er givet ved fig 4.26.
Dette er en sandhedstabel ligesom fig 4.13, men den er "vendt på siden", hvilket
kan være forvirrende, hvis man har vænnet sig til at læse dem der er opstillet som
4.13 er.

Man kan beregne hvert enkelt output bit efter samme metode som beskrevet i forrige
afsnit. PRØV DET for f.eks. "RegWrite".



## Beregning af den indlejrede konstant

ImmGen er meget forvirrende beskrevet i COD. Jeg kan varmt anbefale figur 2.3 og 2.4
i https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf

Man kan opfatte ImmGen som endnu en sekundær afkoder, og det ville have været
smart, hvis COD havde beskrevet den som sådan. I stedet er den vist som en klump
der har hele instruktionen som input. Her kunne man med fordel have indføjet et
styresignal fra den primære afkoder "Control" til "ImmGen" idet beregningen af
immediate afhænger af instruktionsformatet, og det kan bestemmes alene fra "opcode",
så falder mere naturligt som en opgave for den primære afkoder.

I stedet må vi formode at ImmGen i bogen har sin egen afkodning af "opcode" for at
bestemme instruktionsformatet.

Hvad enten denne afkodning finder sted ved at udvide "Control" eller ved at lægge
en afkoder inden i "ImmGen", så kan den beskrives som en sandhedstabel på samme
form som fig 4.26, blot med outputs R,I,S,B,U og J for de 6 forskellige instruktions-formater.

PRØV DET - opstil sandhedstabellen!

Du skal nok tilføje instruktioner, da de få der er med i COD's eksempel ikke
repræsenterer alle de mulige formater.

