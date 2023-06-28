
## Realisme

Lærebogens [COD] 5-trins pipeline er meget brugt i introducerende undervisning, men den er ikke
repræsentativ for nutidens mikroarkitektur. Før vi går i detaljer med mere avanceret mikroarkitektur skal
vi kigge kort på de barske realiteter i moderne CMOS.

### Sløve ledninger og hurtige transistorer

Fig 4.28 og 4.29 i [COD] angiver hvor lang tid en instruktion skal bruge til forskellige
aktiviteter i en tænkt mikroarkitektur. Balancen mellem de forskellige aktiviteter (ca samme tid til
ALU operation som til cache tilgang, f.eks.) svarer til situationen for over 20 år siden.

Der er to væsentlige ændringer siden da:

 * Kommunikation er blevet langsommere relativt til beregning
 * energiforbrug er alt dominerende begrænsning

Her vil vi kun forholde os til den første ændring.

Kommunikation inkluderer her at sende et signal en bestemt afstand såvel som at
sende et signal fra en til mange modtagere. Langsommere kommunikation 
rammer ting som læsning fra registre eller fra cache med større effekt end det rammer 
ALU-operationer. En anden ting der bliver ramt er lange forwarding-netværk.

Her er til sammenligning nogle mere realistiske tidsforbrug for forskellige aktiviteter

 * Cache læsning: 500ps (32 KByte)
 * Register læsning: 100-200ps (32 regs - 256 regs)
 * ALU operation: 100ps
 * Forwarding net: 50-100ps (afhænger af datavejens størrelse)

Bemærk at især tilgang til cache er markant langsommere relativt til resten.

### Lange pipelines

På grund af (især) den relativt langsommere tilgang til cache bliver moderne pipelines
længere end bogens. I almindelighed bruges 3 pipeline trin til cache-tilgang. Vi vil ikke
gå i detaljer med hvad der sker i disse tre trin - de er bare trin Fa,Fb og Fc samt Ma, Mb og Mc.

#### Udfordringer ved instruktionshentning
Lad os genbruge eksemplet fra den superskalare maskine med afkoblet prefetching. Maskinen ser nu således ud:

~~~Test
load:  "Fa Fb Fc Pq De Ex Ma Mb Mc Wb"   depend(Ex,rs1), depend(Ex,rd), produce(Mc,rd)
store: "Fa Fb Fc Pq De Ex Ma Mb Mc"      depend(Ex,rs1), depend(Mc,rs2)
ubetinget hop: "Fa Fb Fc Pq"       	     -
betinget hop:  "Fa Fb Fc Pq De Ex"       depend(Ex,rs1), depend(Ex,rs2)
kald:  "Fa Fb Fc Pq De Ex"               produce(Ex,rd)
retur: "Fa Fb Fc Pq De Ex"               depend(Ex,rs1)
andre: "Fa Fb Fc Pq De Ex Wb"            depend(Ex,rs1), depend(Ex,rs2), depend(Ex,rd), produce(Ex,rd)

ressourcer: Fa:4, Fb:4, Fc4, Pq: 4, De:4, Ex:2, Ag:1, Mm:1, Wb:2

ubetinget hop:                    produce(Pq, Pc)
kald:                             produce(Pq, Pc)
retur:                            produce(Ex, Pc)
betinget hop baglæns taget:       produce(Pq, PC)
betinget hop baglæns ikke taget:  produce(Ex, PC)
betinget hop forlæns taget:       produce(Ex, PC)
betinget hop forlæns ikke taget:  -
~~~
Vort eksempel fra tidligere giver nu følgende plot:

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:     lw   x12,0(x11)          Fa Fb Fc Pq De Ag Ma Mb Mc Wb
4:     addi x11,x11,4           Fa Fb Fc Pq De Ex Wb
8:     sw   x12,0(x10)          Fa Fb Fc Pq >> De Ag Ma Mb Mc
C:     addi x10,x10,4           Fa Fb Fc Pq >> De Ex Wb
10:    bne  x11,x15,0              Fa Fb Fc Pq De Ex
0:     lw   x12,0(x11)                         Fa Fb Fc Pq De Ag Ma Mb Mc Wb
4:     addi x11,x11,4                          Fa Fb Fc Pq De Ex Wb
8:     sw   x12,0(x10)                         Fa Fb Fc Pq >> De Ag Ma Mb Mc
C:     addi x10,x10,4                          Fa Fb Fc Pq >> De Ex Wb
10:    bne  x11,x15,0                             Fa Fb Fc Pq De Ex
0:     ...                                                    Fa De Ex....
~~~

Nu er IPC blot 1.

Det er tydeligt at den længere tilgangstid til instruktionscachen gør det vanskeligt at føde instruktioner til bagenden af maskinen hurtigt nok, selv ved brug af afkoblet prefetching.

#### Branch Target Buffer

Ofte tilføjer man en BTB (Branch Target Buffer) til designet for at forbedre instruktionshentning yderligere. En BTB er en mindre lagerblok som kan tilgås med en del af PC'en og på en enkelt cyklus levere en muligt "branch target". Det gør det muligt at omdirigere instruktionshentning i løbet af Fb, så vi får følgende afviklingsplot:

~~~
                                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
0:     lw   x12,0(x11)          Fa Fb Fc Pq De Ag Ma Mb Mc Wb
4:     addi x11,x11,4           Fa Fb Fc Pq De Ex Wb
8:     sw   x12,0(x10)          Fa Fb Fc Pq >> De Ag Ma Mb Mc
C:     addi x10,x10,4           Fa Fb Fc Pq >> De Ex Wb
10:    bne  x11,x15,0              Fa Fb Fc Pq De Ex
0:     lw   x12,0(x11)                   Fa Fb Fc Pq De Ag Ma Mb Mc Wb
4:     addi x11,x11,4                    Fa Fb Fc Pq De Ex Wb
8:     sw   x12,0(x10)                   Fa Fb Fc Pq >> De Ag Ma Mb Mc
C:     addi x10,x10,4                    Fa Fb Fc Pq >> De Ex Wb
10:    bne  x11,x15,0                       Fa Fb Fc Pq De Ex
0:     ...                                        Fa De Ex....
~~~

Her er IPC 5/3

Det er selvfølgelig ikke altid at en BTB vil udpege den rette adresse, så ovenstående er et optimistisk billede.

#### Udfordringer ved den længere tilgang til datacachen

Lad os prøve med en anden kodestump, en løkke der bestemmer summen af alle elementer i en tabel, men iøvrigt samme maskine:

~~~
while (ptr < limit) { sum += *ptr++; }
~~~

To gennemløb:

~~~
						0  1  2  3  4  5  6  7  8  9
0:  lw x11,0(x10)		Fa Fb Fc Pq De Ag Ma Mb Mc Wb
4:  add x10,x10,4		Fa Fb Fc Pq De Ex Wb
8:  add x12,x12,x11		Fa Fb Fc Pq >> >> >> >> De Ex Wb
C:  bne x10,x13,0		Fa Fb Fc Pq >> >> >> >> De Ex
0:  lw x11,0(x10)		      Fa Fb Fc Pq >> >> De Ag Ma Mb Mc Wb
4:  add x10,x10,4		      Fa Fb Fc Pq >> >> De Ex Wb
8:  add x12,x12,x11		      Fa Fb Fc >> >> >> Pq >> >> >> De Ex Wb
C:  bne x10,x13,0		      Fa Fb Fc >> >> >> Pq >> >> >> De Ex
~~~

For en IPC på 1.

Her er instruktionshentning ikke den begrænsende faktor. I stedet ses det at instruktioner som er afhængige af en load instruktion hurtigt vil kunne putte en prop i maskinen, fordi de skal vente i "De" indtil resultatet fra load instruktionen kan forwardes i slutningen af "Mc".

### Opsamling

Moderne CMOS har langsommere kommunikation relativt til beregning end antaget i COD. 
Det leder til længere pipelines end lærebogens, oftest med 3 trin til cache-tilgang. 
De længere latenstider gør det vanskeligere at udnytte potentialet i pipelining og 
superskalare maskiner. Instruktionshentning kan forbedres med mere avanceret 
"hop forudsigelse", men de langsommere load instruktioner forbliver gift for ydeevnen.
