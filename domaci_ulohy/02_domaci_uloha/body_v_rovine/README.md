# Body v rovině

Úkolem je realizovat program, který pro trojici zadaných bodů ve 2D rovině rozhodne, zda leží na společné přímce.

Vstupem programu jsou X a Y souřadnice trojice bodů ve 2D rovině. Souřadnice jsou zadané jako dvě desetinná čísla, prvé číslo reprezentuje složku X a druhé číslo složku Y.

Program analyzuje vzájemnou polohu zadaných bodů a rozhodne, který ze tří závěrů je platný:

- dva nebo všechny tři zadané body splývají,
- zadané 3 body jsou navzájem různé a neleží na jedné přímce nebo
- zadané 3 body jsou navzájem různé a leží na jedné přímce (pak program navíc určí prostření bod).

Formát výstupu je zřejmý z ukázek níže.
Program musí kontrolovat správnost zadání vstupních dat. Pokud je na vstupu zadaná nesprávná hodnota (nečíselná), pak program detekuje chybu, zobrazí na standardním výstupu chybové hlášení podle ukázky a ukončí se.
```
Ukázky práce programu:
Bod A:
1 2
Bod B:
3 4
Bod C:
5 6
Body lezi na jedne primce.
Prostredni je bod B.
```

```
Bod A:
0.1 0.2
Bod B:
0.3 0.4
Bod C:
0.5 0.6
Body lezi na jedne primce.
Prostredni je bod B.
```
```
Bod A:
10 10
Bod B:
0 10
Bod C:
10 0
Body nelezi na jedne primce.
```
```
Bod A:
0 1
Bod B:
0 3
Bod C:
0 2
Body lezi na jedne primce.
Prostredni je bod C.
```
```
Bod A:
1 0
Bod B:
2 0
Bod C:
-3 0
Body lezi na jedne primce.
Prostredni je bod A.
```
```
Bod A:
1 1
Bod B:
2 2
Bod C:
1 1
Nektere body splyvaji.
```
```
Bod A:
10 20
Bod B:
5 xyz
Nespravny vstup.
```