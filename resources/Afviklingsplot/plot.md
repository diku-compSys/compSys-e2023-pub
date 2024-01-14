# Afviklingsplot og Mikroarkitektur

Opdateret 14. januar 2024 med diverse rettelser.

Opdateret 9. december 2023 med rettelse af "Mm" til "Me" for at matche tidligere introduceret notation.

Opdateret 15. januar 2023 med rettelse af indrykning i svar til øvelse 2.

Opdateret 15. januar 2023 med rettelse af dependencies for superskalar i afsnittet om afkoblet prefetcher.

Opdateret 7. januar 2023 med tilføjelse af "Q*" og "C*" for sw/sh/sb instruktioner.

Afviklingsplot er en kompakt måde at anskueliggøre en computers opførsel under udførelse
af et program. Det kan bruges til at gøre diskussioner af ydeevne konkrete. 
Afviklingsplot kan genereres ud fra regler som udgør en abstrakt beskrivelse af
maskinens mikroarkitektur.

Denne note er et "work in progress". Det er hensigten at nå frem til en formalisme
for beskrivelse af moderne mikroarkitekturer, men det er kun delvis lykkedes på
nuværende tidspunkt. Formodentlig bliver det nødvendigt at skrive en simulator der
kan læse sådan en formel beskrivelse og give en tilfredsstillende simulation af
mikroarkitekturen, før alle fejl er luget ud.

Konstruktive forslag til forbedringer modtages gerne, bedst ved at oprette "issues"
i github.

Oversigt

 * [Introduktion](intro.md)
 * [Superskalare maskiner](superskalar.md)
 * [Moderne CMOS - Realisme](realisme.md)
 * [Out-of-order execution](ooo.md)
 * [Øvelser](exercises.md)
