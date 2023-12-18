# Maskinnær optimering. Opgave A6, Compsys 2023

Finn Schiermer Andersen, December 2023, foreløbig udgave

Denne opgave stilles mandag den 18 december og skal afleveres kl 16 søndag den 7. Januar.



## Opgave

Opgaven består i at optimere en eksisterende implementation af en prioritetskø.

Denne prioritetskø understøtter to forskellige operationer

 * Add(V) - tilføj et element med prioriteten 'V' til prioritetskøen.
 * Take() - udtage det højst prioriterede element fra prioritetskøen.

Elementerne er alene repræsenteret ved et heltal som angiver deres prioritet.
Det laveste heltal er det højest prioriterede element. 
En virkelig brugbar prioritetskø ville lagre andet end prioriteten, i det mindste
en form for identifikation (et andet tal). Det ser vi bort fra i denne opgave.

Det udleverede program læser input fra en fil. Filen består af kommandoer
udformet som tal. Et ikke negativt tal V fortolkes som en kommando der skal udføre
Add(V), dvs tilføje tallet V til prioritetskøen. Et negativt tal -N fortolkes som 
N udførsler af Take(), dvs N gentagne udtagninger af det højest prioriterede element
i prioritetskøen.

Det udleverede program udskriver de værdier der udtages ved Take() til en
anden fil. Fil I/O understøttes med nye systemkald i reference simulatoren og
nye funktioner i det minimale bibliotek "lib.c". Det er ikke en del af opgaven
at optimere I/O.

Den udleverede kode anvender et radix træ til at holde elementerne i
prioritetskøen sorteret. Dette skulle sikre den teoretisk bedst mulige asymptotiske
kompleksitet for en opgave af denne art. Opgaven i A6 består i at skrive en implementation
som er hurtigere for et sæt af inddata der beskrives nærmere nedenfor.

Det er tilladt (men ikke nødvendigvis en god ide) at lave en helt ny løsning
fremfor at basere sig på det udleverede.

Det frarådes at forsøge optimering ved at skrive direkte i RISCV assembler.
Koden bør skrives i C, men det kan være relevant at konsultere den derfra
producerede assemblerkode.

Besvarelsen skal indeholde:

* En kort rapport. Rapporten skal indeholde:
  * En kort præsentation af hvordan man har løst opgaven og hvorfor
  * En analyse af om løsningen også vil være hurtigere for større datasæt
    end de, der praktisk kan afvikles indenfor rammerne af opgaven.
* En hurtigere implementation end den udleverede
* Dokumentation for at denne implementation virker
* Dokumentation for at denne implementation er hurtigere (se nedenfor).

Reference simulatoren kan producere en eksekverings-profil, som beskrives nedenfor.
Den kan hjælpe med at forstå programmers tidsforbrug.



## Inddata og definition af "hurtigere program"

For et givet program og givne inddata er "hurtigere program", det program som
den til opgaven udleverede reference simulator angiver tager færrest clock-cykler.

Reference simulatoren indeholder en model af en pipelinet maskine, der kan angive
hvor mange clock cykler en kørsel tager.

 * Den simulerede maskine er en 9-trins pipeline, "Fa Fb Fc De Ex Ma Mb Mc Wb", 1 instruktion pr trin.
 * Pipelinen stall'er hvis en instruktion har brug for en operand der ikke er tilgængelig endnu
   (den er in-order)
 * Pipelinen stall'er ikke ved et cache-miss, den kan forsætte indtil en afhængig
   instruktion får brug for data (jvf ovenstående).
 * Den primære data cache er 16 kilobytes, 4 vejs associativ med 64 byte blokke og 3 clocks adgangstid
 * Den sekundære cache er 256 kilobytes, 8 vejs associativ med 64 byte blokke og 12 clocks adgangstid
 * Hovedlageret har 50 clocks adgangstid.
 * Caching af instruktioner indgår ikke i modellen, kun caching af data.
 * Forudsigelse af hop/kald/retur indgår ikke i modellen. I stedet regnes blot en
   clock-cyclus for et ikke taget hop og to for et taget (inklusiv kald og retur).

Små inddatasæt kan naturligvis skrives i hånden, men vi udleverer et program, "generate"
som kan generere inddatasæt med mere substans. Ved sammenligning af programmer SKAL
bruges inddatasæt a.in, b.in og c.in produceret med "generate" med følgende parametre:

~~~
./generate a 200 10000 20000 100 5000
./generate b 20000 100 500 10 500
./generate c 5000 10 500 50 200
~~~

Generate vil også producere en reference fil for hver inddatafil, a.ref, b.ref og c.ref.
Uddata fra kørsel af den udleverede prioritetskø med de givne inddata vil producere
uddata som matcher reference filerne.

Hvis i laver inkrementelle ændringer kan I udnytte dette setup til løbende at validere
at jeres løsning virker korrekt.

## Udleverede filer

En ny simulator (eksekverbar for linux og mac) vil være at finde i tools/simulator
i det offentlige repo. Generatoren vil være at finde i tools/generator i det offentlige
repo.

Den udleverede implementation af prioritetskøen findes i filen "radix.c" i filen
"assignments/A6/src/radix.c". Den oversættes til .dis format vha krydsoversætteren
som for A5. Vi anbefaler stadig lokal installation af krydsoversætteren, hvis
muligt, men hvis det ikke dur er der nu adgang til en krydsoversætter i skyen,
se evt tidligere annoncering om dette på Absalon.

## Eksekveringsprofil

Den opdaterede reference simulator kan producere en eksekverings-profil.
Det er en udskrivning af programmet på assembler niveau, hvor hver instruktion
er annoteret med data der kan være relevant for at forstå programmets afviklings-hastighed.

Her ses profilen for fib(10):

~~~
00010074 <fib>:
10074 :        177    0   1       0   0   0    addi     sp,sp,-16       
10078 :        177    0   1      98   0   1    sw       ra,12(sp)       
1007c :        177    0   1     100   0   0    sw       s0,8(sp)        
10080 :        177    0   1     100   0   0    sw       s1,4(sp)        
10084 :        177    0   1       0   0   0    mv       s0,a0           
10088 :        177    0   1       0   0   0    li       a5,1            
1008c :        177    0   1       0   0   0    bgeu     a5,a0,100b0      <fib+0x3c>              
10090 :         88    0   1       0   0   0    addi     a0,a0,-1        
10094 :         88    0   1       0   0   0    auipc    ra,0x0          
10098 :         88    0   1       0   0   0    jalr     -32(ra)          # 10074 <fib>
1009c :         88    0   1       0   0   0    mv       s1,a0           
100a0 :         88    0   1       0   0   0    addi     a0,s0,-2        
100a4 :         88    0   1       0   0   0    auipc    ra,0x0          
100a8 :         88    0   1       0   0   0    jalr     -48(ra)          # 10074 <fib>
100ac :         88    0   1       0   0   0    add      a0,s1,a0        
100b0 :        177    0   4     100   0   0    lw       ra,12(sp)       
100b4 :        177    0   4     100   0   0    lw       s0,8(sp)        
100b8 :        177    0   4     100   0   0    lw       s1,4(sp)        
100bc :        177    0   1       0   0   0    addi     sp,sp,16        
100c0 :        177    0   1       0   0   0    ret     
 |               |    |   |       |   |   |
 |               |    |   |       |   |   pct tilgang til lageret
 |               |    |   |       |   pct hit i L2 cache
 |               |    |   |       pct hit i L1 cache
 |               |    |   latenstid (tid fra Ex til resultat tilgængeligt)
 |               |    ventetid (clocks hvor pipelinen stall'er indtil input data er tilgængelige)
 |               antal gange den pågældende instruktion er udført
 Addresse på instruktionen
~~~

## Anbefalet fremgangsmåde

Forstå det udleverede program. Det kan være svært. Forslag:

 * Opstil et helt lille eksempel på inddata og forventet uddata.
 * Gennemløb C programmet på papir med dit minimale inddata.
 * Tegn data strukturen undervejs
 * Indsæt nogle udskrivninger som kan vise, hvilke valg programmet træffer
 * Kør programmet med dit minimale inddata. Hold programmets valg op i mod dine forventninger
 * Iterer indtil det giver mening :-)

Når du har dannet et overblik over hvordan programmet virker, kan du forsøge
at optimere det. Formodentlig har selve arbejdet med at forstå programmet affødt
spørgsmål du kan bruge. Endvidere kan du bruge simulatoren til at lave en eksekveringsprofil.
Den kan give en ide om, hvor det kan betale sig at optimere.

Det er også en mulighed at lave sin egen løsning fra scratch. 
Det kan synes tillokkende bare at starte forfra, hvis det synes 
svært at forstå den udleverede kode. Men det er også svært.
Overvej nøje om det er en god ide.

