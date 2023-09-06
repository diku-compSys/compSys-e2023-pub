# Introduktion
Dette dokument beskriver hvordan git kan installeres, sættes op, og en kort opskrift på de mest brugte funktioner, git har at tilbyde. Husk altid kommandoen `git status`, hvis I er I tvivl om, hvilken situation I står i.

## Installation og opsætning af git og depot
(Ubuntu/Debian)
`sudo apt update && sudo apt install git`
(MacOS) 
Installér brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
`brew install git`
Kontrollér git er installeret korrekt:
`git --version`

Sæt brugernavn og mail. Disse informationer knyttes til jeres commits.

`git config --global user.name "whatever user name you want"`
`git config --global user.email "email you created your github account with"`

## Opsætning af SSH
Dette er nødvendigt for at kunne klone depotet, samt lave commits.

Følg instruktionerne i sektionerne "Generating a new SSH key" og "Adding your SSH key to the ssh-agent" i følgende link.
https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
Gå derefter til dette link og følg instruktionerne.
https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account

## Oprettelse af depot
Dette trin foretages kun af en person i jeres gruppe

1. Gå til github.com og lav et nyt depot.
1. Lav en ny mappe der skal blive til jeres nye depot (Repository).
1. `git clone git@github.com:larspeterjeppesen/tester.git`
1. (Alternativ til clone) Kør depotinitialiseringskoden i terminalen
  * Dette skaber en README.md fil. Ellers er der ikke forskel.

## For gruppemedlemmer, der skal hente depotet
1. Bliv inviteret til at være medlem af depotet af depotskaberen
  * github.com/username/depotnavn -> Settings -> Collaborators -> Add people
1. Klon depotet som beskrevet i forrige trin

## git status
Det være behjælpeligt at bruge kommandoen `git status` mellem alle andre git-kommandoer, da det giver værdifuld information om den nuværende situation, I står i.

## Tilføjelse af filer til depot:
1. `git add .` eller `git add filnavn`
1. `git commit -m "commit tekst"`
1. `git push -m`

## Løs en merge konflikt:
1. Tilføj en linje til en fil fra din kammerats computer
1. Tilføj en linje fra din terminal til samme fil og push
1. `git pull --rebase`
1. Måske kan git selv løse konflikten. Hvis ikke:
  * Redigér filen, der er konflikt i manuelt
  * `git add "filnavn"` til at markere over for git at konflikten er løst.
  * `git rebase --continue`
  * `git push`



## Gem ændringer, som ikke skal skubbes
1. `git stash -u`
1. `git pull`
1. `git stash pop`

## Ignorér filer ved push
Lav .gitignore fil i roden af jeres depot
* For at ignorere alle filer med en filendelse: tilføj `*.<filendelse>` til .gitignore filen
* Eks: `echo "*.txt" >> .gitignore`
* Eks til at ignorere filer uden filendelser:
<pre># Ignorer alt
*

# fjern ignorering af filer med filendelser
!*.*

# fjern ignorering af mapper
!*/ </pre>
Ovenstående er nyttig til at undgå at skubbe compilerede C-filer, som ikke har nogle filendelser. Dette gør muligvis jeres gruppearbejde lettere.


https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent

## Fjern et commit (`git revert`):
1. Redigér eller tilføj en fil.
1. `add`, `commit`, `push` denne fil.
1. `git log`
1. Kopiér commit-referencen. Det er en hash der ser sådan her ud: `dab5e9478a9f339d30c16ed541fdfbcfeabb4d20`
1. `git revert <commit-referencen>`. F.eks. `git revert dab5e9478a9f339d30c16ed541fdfbcfeabb4d20`
1. Dette laver et nyt commit, som fjerner indholdet af det commit, som blev tilføjet i det commit, I har refereret til.
1. `git push`
Ændringerne er nu tilføjet.
