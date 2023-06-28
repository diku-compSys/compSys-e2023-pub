## Introduktion

Nedenfor ses et afviklingsplot for fire instruktioner på en fem-trins pipeline med
fuld forwarding svarende til beskrivelsen i [COD p. 317] (det er ikke det samme program som i COD)

~~~
                        0  1  2  3  4  5  6  7  8
lw   x11,0(x10)         Fe De Ex Mm Wb
addi x11,x11,100           Fe De De Ex Mm Wb
sw   x11,0(x14)               Fe Fe De Ex Mm Wb
addi x10,x10,1                      Fe De Ex Mm Wb
~~~

Instruktionerne står til venstre, en per linie, og programmet afvikles oppefra og ned. 
Tiden går fra venstre mod højre og udtrykkes i clock-cykler. Af diagrammet kan man 
aflæse tidspunktet for hver aktivitet for hver instruktion.

Programstumpen har en IPC på 0.8 på den simple pipeline. 

I diagrammet angives følgende fem aktiviter:

~~~
Fe - Instruktionshentning (fetch)
De - Instruktionsafkodning (decode)
Ex - Udførelse af aritmetik (execute)
Mm - Tilgang til lager hvis load eller store (memory)
Wb - Opdatering af registre med resultat (writeback)
~~~

### Beskrivelse af Flow

Vi beskriver instruktioners "flow" gennem pipelinen ved at knytte en sekvens af 
aktiviteter til klasser af instruktioner.

I pipelinen i COD er flowet simpelt:

~~~
alle: "Fe De Ex Mm Wb"
~~~

I en simpel pipeline har alle instruktioner samme flow gennem pipelinen.

### Ressourcebegrænsninger

Vi kan beskrive maskinens ressourcer ved antallet af instruktioner som kan udføre 
samme aktivitet på samme tidspunkt. For den simple pipeline angives ressourcebegrænsningen 
ved

~~~
Fe: 1, De: 1, Ex: 1, Mm: 1, Wb: 1
~~~

Betragt vort tidligere eksempel igen:

~~~
                        0  1  2  3  4  5  6  7  8
lw   x11,0(x10)         Fe De Ex Mm Wb
addi x11,x11,100           Fe De De Ex Mm Wb
sw   x11,0(x14)               Fe Fe De Ex Mm Wb
addi x10,x10,1                      Fe De Ex Mm Wb
~~~

Instruktion nr 2 er udsat for et "stall" - den kan ikke fuldføre aktiviteten "De" 
i cyklus 2 og må gentage den i cyklus 3.
Ressourcebegrænsningen for den simple pipeline tillader kun en instruktion i "De" 
ad gangen. Denne begrænsning tvinger instruktion nr 3 til også at "stalle" og gennemføre 
aktiviteten "Fe" to gange. (Vi vender tilbage til hvorfor instruktion nr 2 staller senere)

I en simpel pipeline er det praktisk at modellere det som om alle instruktioner 
bruger de samme ressourcer. Vi ved godt at kun load og store tilgår lageret og 
derfor har brug for et pipeline-trin til det formål, men da alle instruktioner 
tvinges igennem dette pipeline-trin kan man vælge at ignorere det.

I en mere kompliceret pipeline vil man opdele instruktionerne i flere klasser fordi 
forskellige instruktioner har brug for forskellige ressourcer. En tænkt eksempel: 
en maskine hvor kun load og store har et pipeline-trin for lagertilgang, mens de 
øvrige instruktioner kan gå direkte fra "Ex" til "Wb" - og "store" instruktioner 
kan helt undvære Wb:

~~~
load: "Fe De Ex Mm Wb"
store: "Fe De Ex Mm"
andre: "Fe De Ex Wb"
Fe: 1, De: 1, Ex: 1, Mm: 1, Wb: 1
~~~
På denne maskine får vi følgende afviklingsplot for kodestumpen fra tidligere:

~~~
                        0  1  2  3  4  5  6  7  8
lw   x11,0(x10)         Fe De Ex Mm Wb
addi x11,x11,100           Fe De De Ex Wb
sw   x11,0(x14)               Fe Fe De Ex Mm
addi x10,x10,1                      Fe De Ex Wb
~~~

Vi kan gøre det nemmere at spotte hvornår en instruktion "hænger" (aka "stall"), ved at angive
det med ">>" fremfor med den relevante aktivitet:

~~~C
                        0  1  2  3  4  5  6  7  8
lw   x11,0(x10)         Fe De Ex Mm Wb
addi x11,x11,100           Fe >> De Ex Wb
sw   x11,0(x14)               >> Fe De Ex Mm
addi x10,x10,1                      Fe De Ex Wb
~~~

Bemærk at selvom vi markerer et stall med ">>" så er den relevante resource stadig i
brug...og den relevante ressource er den der bruges *efter* stall'et. I eksemplet 
ovenfor er De og Fe således optaget i cyklus 2.

Det er en smagssag om man vil bruge denne særlige markering for stall eller ej. Vi
bruger den her, hvis vi vil gøre det særligt nemt at se stall i diagrammet.

### Dataafhængigheder

Dataafhængigheder specificeres ved at angive hvilke aktiviteter der producerer og/eller afhænger af en værdi. Eksempel:

~~~
load: "Fe De Ex Mm Wb"   depend(Ex,rs1), produce(Mm,rd)
store: "Fe De Ex Mm"     depend(Ex,rs1), depend(Mm,rs2)
andre: "Fe De Ex Wb"     depend(Ex,rs1), depend(Ex,rs2), produce(Ex,rd)
~~~
Her refererer "rs1", "rs2" og "rd" til de to kilderegistre og destinationsregisteret på samme måde som på den grønne side forrest i COD.
Ideen er at en instruktion der anfører depend(Ex,rs1) tidligst kan gennemføre "Ex" i en cyklus efter at rs1 er blevet produceret.

Ovenstående specifikation svarer til en pipeline med fuld forwarding og vil resultere i det afviklingsplot vi allerede har set.

Vi kan beskrive en pipeline helt uden forwarding således:

~~~
load: "Fe De Ex Mm Wb"   depend(Ex,rs1), produce(Wb,rd)
store: "Fe De Ex Mm"     depend(Ex,rs1), depend(Ex,rs2)
andre: "Fe De Ex Wb"     depend(Ex,rs1), depend(Ex,rs2), produce(Wb,rd)
~~~
Hvilket giver anledning til dette afviklingsplot:

~~~
                        0  1  2  3  4  5  6  7  8  9
lw   x11,0(x10)         Fe De Ex Mm Wb                  produce x11 i Wb i cyklus 4
addi x11,x11,100           Fe >> >> De Ex Wb            depend x11 i Ex i cyklus 5, produce x11 i Wb i cyklus 6
sw   x11,0(x14)               >> >> Fe >> De Ex Mm      depend x11 i Ex i cyklus 7
addi x10,x10,1                         >> Fe De Ex Wb
~~~

Her opnås kun en IPC på 4/7.

### Kontrolafhængigheder (hop, kald, retur)

Kontrolafhængigheder specificeres på samme måde som dataafhængigheder men med angivelse af et særlig register: "PC".
Eksempel:

~~~
retur: produce(Ex, PC)
alle: depend(Fe, PC)
~~~
Angiver at PC opdateres i "Ex" af retur instruktionen og at efter en retur-instruktion kan maskinen tidligst gennemføre "Fe" (instruktionshentning) for efterfølgende instruktioner, når PC er opdateret. Den sidste regel for alle instruktioner: "depend(Fe, PC)" er så indlysende at vi ikke vil anføre den fremover.

Den simpleste håndtering af betingede hop lyder:

~~~
hop taget:       produce(Ex, PC)
hop ikke taget:  -
~~~
Her har et hop der ikke tages ingen betydning for timingen af afviklingen af de efterfølgende instruktioner. Kun hop der tages vil kunne forsinke efterfølgende instruktioner.

En ofte anvendt fremgangsmåde i en simpel pipeline er at hop, der hopper mod en lavere adresse forudsiges som tagne, mens et hop der hopper mod en højere adresse forudsiges ikke tagne. Denne forudsigelse laves i "De", da man er nød til at afkode hoppet for at bestemme adressen. Det giver følgende specifikation:

~~~
hop baglæns taget:       produce(De, PC)
hop baglæns ikke taget:  produce(Ex, PC)
hop forlæns taget:       produce(Ex, PC)
hop forlæns ikke taget:  -
~~~

Her er en sekvens af instruktioner med to hop bagud, det første tages, det andet ikke:

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:      addi    x11,x11,4       Fe De Ex Wb
4:      lw      x12,0(x11)         Fe De Ex Mm Wb
8:      add     x13,x13,x12           Fe >> De Ex Wb
C:      bne     x11,x15,0                >> Fe De Ex            <-- NB: Betingede hop behøver ikke Wb
0:      addi    x11,x11,4                         Fe De Ex Wb
4:      lw      x12,0(x11)                           Fe De Ex Mm Wb
8:      add     x13,x13,x12                             Fe >> De Ex Wb
C:      bne     x11,x15,0                                  >> Fe De Ex
10:     et-eller-andet                                                 Fe De Ex ...
~~~

En IPC på 9/14
