
## Superskalar mikroarkitektur

En maskine der kan udføre to eller flere instruktioner samtidigt kaldes "superskalar".

### Ressourcebegrænsninger

De første superskalare kunne udføre to instruktioner samtidigt. Men det var ikke to vilkårlige instruktioner.
Det gik an at bygge en maskine med to ALUer, men de dyreste ressourcer kunne man stadig kun have en af: multiplikations-kredsløbet og tilgangen til lageret (den primære datacache).

Vi kan beskrive denne ressource-inddeling således:

~~~
load:  "Fe De Ag Me Wb"
store: "Fe De Ag Me"
andre: "Fe De Ex Wb"

ressourcer: Fe:2, De:2, Ex:2, Ag:1, Me:1, Wb:2
~~~
Forkortelsen "Ag" står for "Address generate" som så erstatter brugen af den generelle ALU til at beregne adresser ved lagertilgang.

Her er et plot af to iterationer af en løkke der kopierer data fra et område til et andet:

(Der anvendes statisk hopforudsigelse som beskrevet tidligere så hop der går bagud
forudsiger hentning i De)

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:     lw   x12,0(x11)          Fe De Ag Me Wb
4:     addi x11,x11,4           Fe De Ex Wb
8:     sw   x12,0(x10)             Fe De Ag Me
C:     addi x10,x10,4              Fe De Ex Wb
10:    bne  x11,x15,0                 Fe De Ex
0:     lw   x12,0(x11)                      Fe De Ag Me Wb
4:     addi x11,x11,4                       Fe De Ex Wb
8:     sw   x12,0(x10)                         Fe De Ag Me
C:     addi x10,x10,4                          Fe De Ex Wb
10:    bne  x11,x15,0                             Fe De Ex
0:     ...                                              Fe De Ex....
~~~

for en IPC omkring 1.2 (5/4)

Bemærk at Wb i dette plot ikke gennemløbes i programrækkefølge. Det er en følge af at vi har angivet forskellige længder af "flow" for de forskellige instruktioner, samtidig med at de deler Wb. Uden at overveje det nøje har vi derved specificeret en maskine, som ikke er helt så simpel at bygge. Der er flere udfordringer:

1. Sikring af korrekt skrive-rækkefølge: Hvad hvis to instruktioner begge skal opdatere samme register, men den sidste når Wb før den første?
2. Korrekt hazard-detektion og forwarding: Hvis der er flere instruktioner med samme destinationsregister in-flight, hvilken af dem matcher så en senere instruktions kilde-register?
3. Exception håndtering: Hvad hvis en instruktion med sen Wb trigger en exception, hvilket opdages i Wb eller trinnet før, mens en senere instruktion med tidlig Wb opdaterer sit destinationsregister? Den senere instruktion må logisk set ikke udføres.

Det beskrives senere hvordan disse problemer har en samlet løsning i out-of-order maskiner.

I første omgang håndterer vi problem 1 og 2 ved at tilføje en dataafhængighed på instruktionernes destinationsregister:

~~~
aritmetisk op: depend(Ex,Rs1),depend(Ex,rs2),depend(Ex,rd),produce(Wb,rd)
~~~

Dette vil sikre at der maximalt er en instruktion for hvert register i trinnene fra Ex og frem ad gangen. Det udelukker forkert skrive rækkefølge og det sikrer at operand-referencer er unikke.

Vi løser problem 3 ved at antage eksistensen af en backup-mekanisme som tager kopier af destinationsregistre før de skrives. I tilfælde af en exception bruges backuppen til at retablere registrene til den korrekte tilstand.


### Kontrolafhængigheder

Superskalare maskiner kan nemt blive begrænset af instruktionshentning. Især er betingede hop
en udfordring. Vi skal se kort på to udbredte teknikker der hjælper. En i software og en i hardware.

#### software: løkkeudrulning

En meget anvendt teknik er "løkkeudrulning". Løkkeudrulning består i at man kopierer kroppen af en 
løkke en eller flere gange, således at 2 eller flere gennemløb af den oprindelige løkkekrop i stedet
bliver et enkelt gennemløb af en ny sammensat løkkekrop. F.eks.:

~~~
Loop: <krop>
      beq Loop
LoopDone:
~~~

bliver til

~~~
Loop: <krop>
      bne LoopDone
      <krop>
      beq Loop
LoopDone:
~~~

Det er en teknik som ofte forøger programmers størrelse ganske betydeligt.

Gevinsten kan ses af følgende plot, hvor vi har udrullet løkken fra tidligere:

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:     lw   x12,0(x11)          Fe De Ag Me Wb
4:     addi x11,x11,4           Fe De Ex Wb
8:     sw   x12,0(x10)             Fe De Ag Me
C:     addi x10,x10,4              Fe De Ex Wb
10:    beq  x11,x15,0                 Fe De Ex
14:    lw   x12,0(x11)                Fe De Ag Me Wb
18:    addi x11,x11,4                    Fe De Ex Wb
1C:    sw   x12,0(x10)                   Fe De Ag Me
20:    addi x10,x10,4                       Fe De Ex Wb
24:    bne  x11,x15,0                       Fe De Ex
0:     ...                                        Fe De Ex....
~~~

IPC er her 10/6

#### hardware: afkoblet prefetcher

Det er også muligt at forbedre håndteringen af hop, kald og retur ved at smide flere hardware-ressourcer
efter problemet. En ofte anvendt fremgangsmåde går ud på at splitte pipelinen i en for-ende og en bag-ende 
adskilt af en mindre kø, hvor forenden overdimensioneres. Dette design tillader forenden at "kigge frem"
i instruktionsstrømmen og forudsige hop, kald og retur tidligere. Det er nødvendigt at udvide pipelinen
med to trin mellem Fe og De som vi vil kalde "Pr" og "Qu" hvilket står for henholdsvis "predict" og "queue". 

Denne form for mikroarkitektur siges at have "afkoblet prefetching" (eller "aggressiv prefetching")

Her er et eksempel på specifikationen af sådan en maskine:

~~~Text
load:          "Fe Pr Qu De Ag Me Wb"  depend(Ex,rs1), produce(Me,rd)
store:         "Fe Pr Qu De Ag Me"     depend(Ex,rs1), depend(Me,rs2)
ubetinget hop: "Fe Pr"                 -
betinget hop:  "Fe Pr Qu De Ex"        depend(Ex,rs1), depend(Ex,rs2)
kald:          "Fe Pr Qu De Ex"        produce(Ex,rd)
retur:         "Fe Pr Qu De Ex"        depend(Ex,rs1)
andre:         "Fe Pr Qu De Ex Wb"     depend(Ex,rs1), depend(Ex,rs2), produce(Ex,rd)

ressourcer: Fe:4, Pr: 4, Qu:4, De:2, Ex:2, Ag:1, Me:1, Wb:2

ubetinget hop:                    produce(Pq, Pc)
kald:                             produce(Pq, Pc)
retur:                            produce(Ex, Pc)
betinget hop baglæns taget:       produce(Pq, PC)
betinget hop baglæns ikke taget:  produce(Ex, PC)
betinget hop forlæns taget:       produce(Ex, PC)
betinget hop forlæns ikke taget:  -
~~~

To iterationer af vores løkke fra tidligere afsnit giver følgende plot:

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:     lw   x12,0(x11)          Fe Pr Qu De Ag Me Wb
4:     addi x11,x11,4           Fe Pr Qu De Ex Wb
8:     sw   x12,0(x10)          Fe Pr >> Qu De Ag Me
C:     addi x10,x10,4           Fe Pr >> Qu De Ex Wb
10:    bne  x11,x15,0              Fe Pr >> Qu De Ex
0:     lw   x12,0(x11)                   Fe Pr Qu De Ag Me Wb
4:     addi x11,x11,4                    Fe Pr Qu De Ex Wb
8:     sw   x12,0(x10)                   Fe Pr >> Qu De Ag Me
C:     addi x10,x10,4                    Fe Pr >> Qu De Ex Wb
10:    bne  x11,x15,0                       Fe Pr >> Qu De Ex
0:     ...                                        Fe Pr Qu De Ex....
~~~

Også her er IPC 10/6

#### Diskussion

I praksis er de to teknikker ikke lige gode. Løkke-udrulning hjælper kun på løkker,
mens afkoblet prefetching også hjælper på andre programkonstruktioner.

Ofte er begge teknikker i brug. Processoren har afkoblet prefetch *og* compileren vil
udrulle mindre løkker, hvis man tilvælger optimeret kodegenerering.
