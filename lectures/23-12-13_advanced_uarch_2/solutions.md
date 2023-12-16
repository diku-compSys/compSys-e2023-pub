
# Løsninger til øvelser 13. december


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
    -                                                 Qu -- -- -- -- pk rd st
    bge  x9,x4,Loop              Fa Fb Fc De Fu Al Rn Qu pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1                    Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- Ca Cb
    slli x11,x4,5                   Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11                   Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)                    Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2                         Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- Ca Cb
    add  x12,x17,x12                      Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)                          Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc -- Ca Cb
    -                                                             Qu -- -- -- -- pk rd st
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
    -                                           Qu -- -- -- -- -- -- pk rd st
    bge  x9,x4,Loop        Fa Fb Fc De Fu Al Rn >> Qu pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1              Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    slli x11,x4,5             Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11          Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)           Fa Fb Fc De Fu Al Rn >> Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2                Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- -- Ca Cb
    add  x12,x17,x12             Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- -- Ca Cb
    sw   x11,0(x12)              Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ag ma mb mc -- -- Ca Cb
    -                                                    Qu -- -- -- -- -- -- pk rd st
    bge  x9,x4,Loop              Fa Fb Fc De Fu Al Rn >> Qu pk rd ex -- -- -- -- -- -- -- Ca Cb

### Spg 1.3

Hvad er IPC for 20 gennemløb af løkken?

### Svar 1.3

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
    -                                        Qu -- -- -- -- -- -- -- pk rd st
    bge  x9,x4,Loop     Fa Fb Fc De Fu Al Rn Qu -- pk rd ex -- -- -- -- -- -- Ca Cb
    addi x4,x4,1           Fa Fb Fc De Fu Al Rn Qu pk rd ex wb -- -- -- -- -- Ca Cb
    slli x11,x4,5          Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- Ca Cb
    add  x11,x16,x11       Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- Ca Cb
    lw   x11,8(x11)        Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc wb Ca Cb
    slli x12,x4,2          Fa Fb Fc De Fu Al Rn Qu -- pk rd ex wb -- -- -- -- -- Ca Cb
    add  x12,x17,x12       Fa Fb Fc De Fu Al Rn Qu -- -- pk rd ex wb -- -- -- -- Ca Cb
    sw   x11,0(x12)        Fa Fb Fc De Fu Al Rn Qu -- -- -- pk rd ag ma mb mc -- Ca Cb
    -                                           Qu -- -- -- -- -- -- -- pk rd st
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

Opstil en risc-v kodesekvens:

 * hvor en load der følger efter en store tilgår samme adresse og derfor skal "se" data fra store instruktionen
 * hvor store data endnu ikke er tilgængelig i store-køen på det tidspunkt, hvor load instruktionen skal bruge det

diskuter/opstil/giv en mere præcis definition af det sidste af disse to krav.

## Svar 2

Opgaven kræver ikke opstilling af et afviklingsplot, men det gør diskussionen nemmere:
(her for en 2-vejs med 1 opslag i cache pr clock)

~~~
lw  x3,0(x4)   Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
lw  x2,0(x3)   Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ag ma mb mc wb Ca Cb
sw  x2,0(x5)      Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- -- -- -- Ca Cb
-                                      Qu -- -- -- -- -- -- -- pk rd st Ca Cb
lw  x3,0(x5)      Fa Fb Fc De Fu Al Rn Qu -- pk rd ag ma mb mc -- -- -- wb Ca Cb
~~~

Det spørgsmål som kunne diskuteres er hvor sent data kunne ankomme til store-køen
og stadig forwardes af den afhængige load instruktion i tide.

I noten om afviklingsplot ser det ud til at "wb" kan finde sted umiddelbart efter "st",
som er der, hvor værdien skrives til store-køen, så det kan fungere som præcis definition.
Det beskrives dog ikke præcis hvordan dette tænkes opnået.



## Opgave 3

### Spg 1

Opstil en risc-v kodesekvens:

 * hvor en load der følger efter en store tilgår samme adresse og derfor skal "se" data fra store instruktionen
 * hvor store addressen endnu ikke er tilgængelig i store-køen på det tidspunkt, hvor load instruktionen har brug
   for at sammenligne addresser.

diskuter/opstil/giv en mere præcis definition af det sidste af disse to krav.

### Svar 3.1

Det er ikke nødvendigt at opstille et afviklingsplot - tilstrækkeligt at angive
de tre instruktioner nedenfor, men....

~~~
lw  x3,0(x4)   Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
sw  x2,0(x3)   Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ag ma mb mc Ca Cb
-                                   Qu pk rd st -- -- -- -- -- -- -- Ca Cb
lw  x3,0(x5)      Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- -- -- wb Ca Cb
~~~

Det spørgsmål som kunne diskuteres er hvor sent adressen kunne ankomme til store-køen
og stadig "ses" af den senere load, som enten skal forwarde data fra store-køen
eller fra datacachen alt afhængig af adressen.

Så en rimelig antagelse ville være at en tidligere store skal have fuldført "ag" før at
en senere load udfører "ag" for den senere load-instruktion kan "se" store instruktionens addresse.

### Spg 2

Opstil et afviklingsplot som illustrerer ovenstående på en 4-vejs out-of-order mikroarkitektur med en
cache tilgang pr clock. Diskuter evt hvornår load instruktionen tidligst kan gennemføre et writeback.

### Svar 3.2

~~~
lw  x3,0(x4)   Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc wb Ca Cb
sw  x2,0(x3)   Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ag ma mb mc Ca Cb
-                                   Qu pk rd st -- -- -- -- -- -- -- Ca Cb
lw  x3,0(x5)   Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- -- -- -- wb Ca Cb
~~~

I noten om afviklingsplot ser det ud til at "wb" for en load kan finde sted umiddelbart efter "mc"
for en tidligere store, hvilket er 3 clocks efter adresseberegningen for den tidligere store. 
Det beskrives dog ikke præcis hvordan dette tænkes opnået.

Man kan forestille sig at de tre clocks er krævet fordi der er mange adresser at sammenligne.


### Spg 3

I forlængelse af spg 2. Diskuter hvornår en instruktion som afhænger af load-instruktionen tidligst
vil kunne begynde udførelse.


### Svar 3.3

Her er spørgsmålet hvor tidligt scheduleren kan nå at vække en afhængig instruktion.

Betragt:

~~~
                                                         0  1  2  3  4  5
sw  x2,0(x3)   Fa Fb Fc De Fu Al Rn Qu -- -- -- -- pk rd ag ma mb mc Ca Cb
-                                   Qu pk rd st -- -- -- -- -- -- -- Ca Cb
lw  x3,0(x5)   Fa Fb Fc De Fu Al Rn Qu pk rd ag ma mb mc -- -- -- -- wb Ca Cb
add x3,x3,x7   Fa Fb Fc De Fu Al Rn Qu -- -- -- -- -- -- -- -- pk rd ex wb Ca Cb
~~~

Her beregnes adressen for den tidligere store-instruktion i cycle 0. Sammenligning med
ventende load instruktioner kan tidligst ske fra begyndelsen af cycle 1. For at den sidste
instruktion som er afhængig af load-instruktionen kan nå "ex" i cycle 4 skal scheduleren
udvælge den i cycle 2. Det virker lovlig optimistisk, men matcher eksempler fra
forelæsningsslides. Vi kender ikke det korrekte svar, men det ville ikke overraske,
hvis add instruktionen ville være forsinket yderligere et par cycles i forhold til ovenstående
afviklingsplot.



