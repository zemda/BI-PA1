# Hodnocení předmětu

Úkolem je vytvořit program, který dokáže vyhledávat v zadaných bodových hodnoceních.

Vstupem našeho programu je seznam bodových hodnocení v předmětu PA1. Jedna vstupní hodnota bodů představuje hodnocení jednoho studenta. Následně chceme tato data analyzovat. Tedy chceme zjistit, kolik studentů připadá na zadaný interval bodového hodnocení.

Vstupem je nejprve seznam bodových hodnocení. Bodové hodnocení studenta je celé číslo v intervalu 0 až 1000000000 včetně. Bodová hodnocení jsou zadaná ve složených závorkách, jednotlivé hodnoty jsou oddělené právě jednou čárkou. Po zadání bodových hodnocení přicházejí dotazy. Každý dotaz je zadaný jako interval (uzavřený, polootevřený, otevřený), meze intervalu jsou zadané jako celá čísla, čísla jsou oddělená středníkem. Intervalů může být zadaných mnoho, zpracování dotazů pokračuje do konce vstupu (EOF).

Výstupem programu je počet studentů, který dosáhl bodového hodnocení pro každý dotazovaný interval.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

- hodnocení studentů není zadané jako celé číslo v intervalu 0 až 1000000000,
- hodnocení studentů není ve složených závorkách,
- hodnocení studentů nejsou oddělena čárkou,
- musí být zadaný alespoň jeden hodnocený student,
- dotazovaný interval není zadaný jako otevřený, polootevřený ani jako uzavřený,
- meze dotazovaného intervalu nejsou celá čísla (mohou být i záporná),
- meze dotazovaného intervalu nejsou oddělené středníkem.


Ukázka práce programu:

```Pocty bodu:
{ 1, 7, 22, 4, 7, 5, 11, 9, 1 }
Intervaly:
<4;7>
 -> 4
<-1000;1000>
 -> 9
<4;4>
 -> 1
(4;4>
 -> 0
(4;7>
 -> 3
(4;7)
 -> 1
<4;7)
 -> 2
<7;7>
 -> 2
<6;8>
 -> 2
(6;8)
 -> 2
<15;19>
 -> 0
<7;4>
 -> 0

```
```
Pocty bodu:
{ 120, 5124, 32, 4
Nespravny vstup.
```
```
Pocty bodu:
{ 120, 5124, 32, 4 }
Intervaly:
( 12, 13 )
Nespravny vstup.
```
```
Pocty bodu:
{ abcd }
Nespravny vstup.
```