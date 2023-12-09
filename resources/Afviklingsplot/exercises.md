# Eksamensrettede øvelser i mikroarkitektur og afviklingsplot

## Opgave 1

Denne opgave handler om forskellige out-of-order maskiners ydeevne ved udførelse
af en og samme stump kode.

Husk at angive eventuelle antagelser du måtte gøre i forbindelse med besvarelsen.


Nedenfor ses to iterationer af en løkke-krop udført på en 2-vejs out-of-order mikroarkitktur med max 1 cache tilgang pr clock

    addi x4,x4,1        Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
    slli x11,x4,5       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb Ca Cb
    add  x11,x16,x11       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb Ca Cb
    lw   x11,8(x11)        Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2             Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- Ca Cb
    add  x12,x17,x12          Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)              Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc -- Ca Cb
    -                                                 Q* -- -- -- -- pk rd st -- C*
    bge  x9,x4,Loop              Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1                    Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- Ca Cb
    slli x11,x4,5                   Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11                   Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)                    Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2                         Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- Ca Cb
    add  x12,x17,x12                      Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)                          Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc -- Ca Cb
    -                                                             Q* -- -- -- -- pk rd st -- C*
    bge  x9,x4,Loop                          Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- Ca Cb

Bemærk at store instruktioner opsplittes i to (cache opslag og data skrivning til skrive-kø)
som scheduleres separat.

### Spg 1.1

Hvad er IPC hvis løkken udføres uendeligt mange gange og alle hop forudsiges korrekt ?

### Svar 1.1

Vi kan se at hver gennemløb koster 4 clock cykler (Fa, Qu og Ca forskydes alle 4 clock cykler, hvis vi kigger på anden iteration af loopet)
Da der er 8 instruktioner i hvert gennemløb får vi en IPC på 2.

Hvis alle hop forudsiges korrekt vil det
også være IPC for uendeligt mange gennemløb.

### Spg 1.2

Hvad er IPC for 20 gennemløb af løkken?

hint: inkluder omkostningen ved den afsluttende fejlforudsigelse.

### Svar 1.2

20 gennemløb af løkken koster 20x4 clocks + omkostningen ved den sidste fejlforudsigelse.

Vi kan illustrere fejlforudsigelsen således:

~~~
    bge  x9,x4,Loop              Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1                                                  Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
~~~

Vi kan se at fejlforudsigelsen koster 10 clock cycles (11, men en enkelt clocks tab er allerede indregnet).
Samlet vil de 20 gennemløb tage 90 clock. Da de indeholder 160 instruktioner får vi IPC = 160/90 = 16/9




Nedenfor ses to iterationer af den samme løkke-krop på en 4-vejs out-of-order mikroarkitektur med max 2 cache tilgange pr clock.

    addi x4,x4,1        Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
    slli x11,x4,5       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb Ca Cb
    add  x11,x16,x11    Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb Ca Cb
    lw   x11,8(x11)     Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2          Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    add  x12,x17,x12       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)        Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc -- Ca Cb
    -                                           Q* -- -- -- -- -- -- pk rd st C*
    bge  x9,x4,Loop        Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- -- Ca Cb
    addi x4,x4,1              Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    slli x11,x4,5             Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11          Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)           Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2                Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    add  x12,x17,x12             Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)              Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc -- Ca Cb
    -                                                 Q* -- -- -- -- -- -- pk rd st C*
    bge  x9,x4,Loop              Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- -- Ca Cb

### Spg 1.3

Hvad er IPC for 20 gennemløb af løkken?

### Svar 1.3

Vi kan se at hver gennemløb koster 2 clock cykler (Fa, Qu og Ca forskydes alle 2 clock cykler),
så 20 gennemløb koster 40 clock. Fejlforudsigelsen koster det samme som i tidligere svar (10 cycles).
Samlet IPC = 160/50 = 16/5 = 3.2

Vi kan se at hver gennemløb koster 2 clock cykler (Fa, Qu og Ca forskydes alle 2 clock cykler),
så 20 gennemløb koster 40 clock. Fejlforudsigelsen koster det samme som i tidligere svar (10 cycles).
Samlet IPC = 160/50 = 16/5 = 3.2




Nedenfor ses to iterationer af den samme løkkekrop på en 8-vejs out-of-order mikroarkitektur
med max 3 cache tilgange pr clock

    addi x4,x4,1        Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
    slli x11,x4,5       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb Ca Cb
    add  x11,x16,x11    Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb Ca Cb
    lw   x11,8(x11)     Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2       Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- -- Ca Cb
    add  x12,x17,x12    Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)     Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc -- Ca Cb
    -                                        Q* -- -- -- -- -- -- -- pk rd st C*
    bge  x9,x4,Loop     Fa Fb Fc De Fu Al Rn Qu -- pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1           Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    slli x11,x4,5          Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11       Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)        Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2          Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- -- Ca Cb
    add  x12,x17,x12       Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)        Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc -- Ca Cb
    -                                           Q* -- -- -- -- -- -- -- pk rd st C*
    bge  x9,x4,Loop        Fa Fb Fc De Fu Al Rn Qu -- pk rd ex -- -- -- -- -- -- Ca Cb

### Spg 1.4

Hvad er IPC for 20 gennemløb af løkken.

### Svar 1.4

Vi kan se at hver gennemløb koster 1 clock cykle (Fa, Qu og Ca forskydes alle 1 clock cykle)
så 20 gennemløb koster 20 clock. Fejlforudsigelsen koster det samme som i tidligere svar (11 cycles).
Samlet IPC = 160/30 = 16/3




### Spg 1.5

hvad vil IPC være for 20 gennemløb af løkken på en 12-vejs ooo med max 4 cache tilgange pr clock ?

Giv en solid begrundelse for dit svar. Opstil om nødvendigt et afviklingsplot.

### Svar 1.5

Der er en dataafhængighed fra hver iteration til den næste via x4.
En iteration kan derfor ikke afvikles hurtigere end den næste værdi for x4 kan produceres.
Da x4 beregnes ved "addi x4,x4,1" som har en latenstid på 1, kan en iteration aldrig afvikles
på mindre end 1 cyclus. IPC bliver således som beregnet i 1.4

Det er ikke nødvendigt at opstille et afviklingsplot.


## Opgave 2

De følgende spørgsmål handler om hvorden nedenstående instruktionssekvens afvikles
på forskellige mikroarkitekturer.

~~~
Loop:   addi x4,x4,4
        addi x6,x6,4
        subi x7,x7,1
        lw   x8,0(x4)
        sw   x8,0(x5)
        bne  x7,x9,Loop
Loop:   addi x4,x4,4
        addi x6,x6,4
        subi x7,x7,1
        lw   x8,0(x4)
        sw   x8,0(x5)
        bne  x7,x9,Loop
~~~

Angiv for hvert spørgsmål eventulle antagelser du gør for at besvare spørgsmålet

### Spg 2.1

Opstil et afviklingsplot for en simpel 5-trins pipeline med fuld forwarding som beskrevet
i COD.

### Svar 2.1

Vi antager

 * At hop forudsiges taget i De.
 * At load data kan forwardes fra starten af Wb til store i Me

~~~
Loop:   addi x4,x4,4            Fe De Ex Mm Wb
        addi x6,x6,4               Fe De Ex Mm Wb
        subi x7,x7,1                  Fe De Ex Mm Wb
        lw   x8,0(x4)                    Fe De Ex Mm Wb
        sw   x8,0(x5)                       Fe De Ex Mm Wb
        bne  x7,x9,Loop                        Fe De Ex Mm Wb
Loop:   addi x4,x4,4                                 Fe De Ex Mm Wb
        addi x6,x6,4                                    Fe De Ex Mm Wb
        subi x7,x7,1                                       Fe De Ex Mm Wb
        lw   x8,0(x4)                                         Fe De Ex Mm Wb
        sw   x8,0(x5)                                            Fe De Ex Mm Wb
        bne  x7,x9,Loop                                             Fe De Ex Mm Wb
~~~


### Spg 2.2

Opstil et afviklingsplot for en 2-vejs superskalar med single-cycle tilgang til cache
som beskrevet først i afsnittet om superskalar mikroarkitektur i noten om afviklingsplot

### Svar 2.2

Vi antager

 * At bagudgående hop forudsiges taget i De.

~~~
Loop:   addi x4,x4,4            Fe De Ex Wb
        addi x6,x6,4            Fe De Ex Wb
        subi x7,x7,1               Fe De Ex Wb
        lw   x8,0(x4)              Fe De Ag Mm Wb
        sw   x8,0(x5)                 Fe De Ag Mm
        bne  x7,x9,Loop               Fe De Ex Wb
Loop:   addi x4,x4,4                        Fe De Ex Wb
        addi x6,x6,4                        Fe De Ex Wb
        subi x7,x7,1                           Fe De Ex Wb
        lw   x8,0(x4)                          Fe De Ag Mm Wb
        sw   x8,0(x5)                             Fe De Ag Mm
        bne  x7,x9,Loop                           Fe De Ex Wb
~~~


### Spg 2.3

Opstil et afviklingsplot for en 4-vejs out-of-order mikroarkitektur med realistisk
(3-trins pipelined) adgang til cache som beskrevet i afsnittet om out-of-order
mikroarkitektur i noten om afviklingsplot.

### Svar 2.3

Vi antager:

 * Korrekt forudsigelse af hop som beskrevet i noten
 * Max to cache tilgange pr clock.

~~~
Loop:   addi x4,x4,4            Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
        addi x6,x6,4            Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
        subi x7,x7,1            Fa Fb Fc De Fu Al Rn Qu pk rd ex wb Ca Cb
        lw   x8,0(x4)           Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc wb Ca Cb
        sw   x8,0(x5)              Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb
        -                                               Q* -- -- -- -- pk rd st C*
        bne  x7,x9,Loop            Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- Ca Cb
Loop:   addi x4,x4,4                  Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- Ca Cb
        addi x6,x6,4                  Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
        subi x7,x7,1                  Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- Ca Cb
        lw   x8,0(x4)                 Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc wb Ca Cb
        sw   x8,0(x5)                    Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- Ca Cb
        -                                                     Q* -- -- -- -- pk rd st C*
        bne  x7,x9,Loop                  Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- Ca Cb
~~~


