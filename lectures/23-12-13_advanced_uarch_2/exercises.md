
# Øvelser 13. december

Bemærk at noten om afviklingsplot er opdateret pr 9. december 2023
for at kunne danne baggrund for de følgende opgaver.


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

### Spg 1.2

Hvad er IPC for 20 gennemløb af løkken?

hint: inkluder omkostningen ved den afsluttende fejlforudsigelse.



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


### Spg 1.5

hvad vil IPC være for 20 gennemløb af løkken på en 12-vejs ooo med max 4 cache tilgange pr clock ?

Giv en solid begrundelse for dit svar. Opstil om nødvendigt et afviklingsplot.



## Opgave 2

Opstil en risc-v kodesekvens:

 * hvor en load der følger efter en store tilgår samme adresse og derfor skal "se" data fra store instruktionen
 * hvor store data endnu ikke er tilgængelig i store-køen på det tidspunkt, hvor load instruktionen skal bruge det

diskuter/opstil/giv en mere præcis definition af det sidste af disse to krav.


## Opgave 3

### Spg 1

Opstil en risc-v kodesekvens:

 * hvor en load der følger efter en store tilgår samme adresse og derfor skal "se" data fra store instruktionen
 * hvor store addressen endnu ikke er tilgængelig i store-køen på det tidspunkt, hvor load instruktionen har brug
   for at sammenligne addresser.

diskuter/opstil/giv en mere præcis definition af det sidste af disse to krav.

### Spg 2

Opstil et afviklingsplot som illustrerer ovenstående på en 4-vejs out-of-order mikroarkitektur med en
cache tilgang pr clock. Diskuter evt hvornår load instruktionen tidligst kan gennemføre et writeback.

### Spg 3

I forlængelse af spg 2. Diskuter hvornår en instruktion som afhænger af load-instruktionen tidligst
vil kunne begynde udførelse.

