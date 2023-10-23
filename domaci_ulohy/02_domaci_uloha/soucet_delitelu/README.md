# Součet dělitelů


Úkolem je realizovat program, který nalezne čísla ze zadaného intervalu, která mají prvočíselný součet svých vlastních dělitelů.

Vlastním dělitelem čísla x je takový jeho dělitel, který je menší než x. Například číslo 27 má vlastní dělitele 1, 3 a 9. Zajímá nás součet všech vlastních dělitelů daného čísla. Například pro číslo 27 je součet jeho vlastních dělitelů roven 1+3+9=13. Protože 13 je prvočíslo, je 27 číslo, které má prvočíselný součet svých vlastních dělitelů. Úkolem programu bude hledat taková čísla na zadaném intervalu hodnot.

Vstupem programu je zadání prohledávaných intervalů. Intervalů může být na vstupu mnoho. Program bude prohledávané intervaly číst ze vstupu a průběžně je odbavovat - prohledávat. Práce programu skončí až na vstupu nebude žádný interval k prohledání (dosáhne se EOF). Každý interval je zadaný jako trojice: ? lo hi nebo # lo hi. Celá čísla lo a hi představují meze prohledávaného intervalu (prohledávají se uzavřené intervaly, tedy včetně mezí). První znak definuje typ odpovědi. Pří zadaném typu hledání ? chceme nalezená čísla vypsat, při typu hledání # chceme pouze zjistit počet takových čísel.

Výstupem programu je odpověď na každý zadaný vstupní interval. Odpovědí je buď seznam nalezených čísel v pořadí od nejmenšího po největší a jejich počet (zadání typu ?) nebo pouze nalezený počet čísel (zadání typu #). Formát výstupu je zřejmý z ukázkových běhů.

Program musí detekovat nesprávný vstup. Pokud je limit zadaný nesprávně (záporný, nečíselný, nulový, ...), program musí situaci detekovat, vypsat chybové hlášení a ukončit se. Za vypsanou chybovou hláškou je odřádkování. Za chybu považujte:

- nesprávný typ odpovědi (povolený je pouze typ ? nebo #),
- mez intervalu není platné celé číslo,
- dolní mez je menší než 1 nebo
- horní mez je menší než dolní mez.

Úloha je hodnocena v bonusovém režimu. Pro získání plného nominálního hodnocení postačuje řešení, které vychází z naivního algoritmu a je rozumně efektivně implementované. V bonusových testech jsou zadávané vysoké horní meze prohledávaných intervalů a počet problémů k vyřešení je velký (stovky intervalů na vstupu).

### Ukázka práce programu:
```
Intervaly:
? 1 10
4
8
Celkem: 2
```
```
Intervaly:
? 27 27
27
Celkem: 1
? 100 120
111
115
Celkem: 2
# 100 120
Celkem: 2
```
```
Intervaly:
? 265 327
265
275
279
291
299
305
309
319
323
324
325
327
Celkem: 12
# 265 327
Celkem: 12
```
```
Intervaly:
# 1761 2242
Celkem: 50
```
```
Intervaly:
# 358 221
Nespravny vstup.
```

```
Intervaly:
! 10 20
Nespravny vstup.
```