# Politicky korektní vyjadřování


Vaším úkolem je vytvořit funkci (ne program, pouze funkci), která dokáže pomoci PR oddělení při formulaci politicky korektních tiskových prohlášení.

S rozvojem naší společnosti je spojená nutnost formulovat své myšlenky tak, aby prohlášení nemohlo nikoho ranit či dokonce urazit. Tomuto trendu se říká politická korektnost, lidově též newspeak. Podobnost s pojmem newspeak z Orwellova románu je pochopitelně čistě náhodná. Označit někoho za "flákače" je prostě nepřípustné, naproti tomu pojem "osoba se specifickou potřebou plánování účasti v pracovním procesu" je zcela jistě univerzálně použitelné.

Vámi implementovaná funkce tomuto procesu bude napomáhat. Vypisovat dlouhé politicky korektní fráze odmítají i osoby bez specifických potřeb plánování účasti v pracovním procesu. Implementovaná funkce bude v textu nahrazovat nevhodné politicky nekorektní formulace za jejich správnou náhradu. Rozhraní funkce bude:

```c
char * newSpeak ( const char * text, const char * (*replace)[2] );
```

Parametry funkce jsou:

- text - původní text, ve kterém má dojít k náhradě nevhodných formulací. Tento parametr je const, tedy funkce jej může pouze číst,
- replace - je pole s dvojicemi řetězců, k nahrazení. Pole replace je dvojrozměrné, obsahuje n řádek a dva sloupce. Ve sloupci 0 je řetězec nevhodné fráze a ve sloupci 1 je její politicky korektní náhrada. Počet řádek pole není explicitně určen, víte ale, že poslední řádka v poli obsahuje dva ukazatele s hodnotou NULL.
- Návratovou hodnotou funkce je řetězec s provedenými náhradami. Tento řetězec musí být funkcí dynamicky alokován (buď malloc nebo realloc). Volající řetězec použije a po jeho použití jej uvolní z paměti (zavolá free). V případě chybných parametrů vrací funkce NULL.

Chceme, aby náhrady v řetězci byly jednoznačné. Toho dosáhneme následujícím:
- text nahrazujeme zleva doprava,
- jednou nahrazený text již není znovu nahrazován, v náhradách pokračujeme za nahrazeným textem (viz např. ukázka "specialist"),
- nahrazované fráze (sloupec 0) jsou jednoznačné, tedy žádný vzor nesmí být předponou jiného vzoru. Funkce před zahájením práce zkontroluje, že toto platí, pokud ne, vrátí chybovou signalizaci hodnotou NULL. V ukázkovém běhu je to porušeno u dvojice fail a failure.

Všechny řetězce, které funkce dostává/vrací jsou C řetězce (nulou ukončené). Při porovnávání řetězců funkce rozlišuje malá a velká písmenka.