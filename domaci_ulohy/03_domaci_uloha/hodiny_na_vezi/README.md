# Hodiny na věži


Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude počítat, kolikrát budou zvonit zvony na věži v zadaném časovém intervalu.

Předpokládáme hodiny na věži, které dokáží zvonit na zvony a tím odbíjet čas. Hodiny jsou vybavené dvojicí zvonů:

- zvon #1, který odbíjí minuty. Zvoní vždy v násobcích 15 minut, zvoní 1x až 4x (XX:00 - 4x, XX:15 - 1x, XX:30 - 2x a XX:45 - 3x).
- zvon #2, který odbíjí hodiny, zvoní tolikrát, kolik ukazuje hodinová ručička. Tedy v půlnoci 12x, v 1:00 1x, ve 2:00 2x, ..., ve 12:00 12x, v 13:00 1x, ve 14:00 2x, ...,
- v neděli je odbíjení po celý den vypnuté. Tedy naposledy se zvoní v sobotu v 23:45 a pak až v pondělí v 00:00.

Naše funkce dostane parametrem dva časové údaje - počátek a konec časového intervalu. Počátek i konec je dán rokem, měsícem, dnem, hodinou a minutou. Funkce spočítá, kolikrát hodiny v tomto intervalu odbijí na jednom a na druhém zvonu. Pro výpočet uvažujeme uzavřený interval, tedy pokud se odbíjí na začátku/konci zadaného intervalu, do výsledku zahrneme i tato odbíjení.

Požadovaná funkce má rozhraní:
```c
int bells ( int y1, int m1, int d1, int h1, int i1,
           int y2, int m2, int d2, int h2, int i2, 
           long long int * b1, long long int * b2 )
```
y1, m1, d1, h1, i1
- jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu počátku intervalu,

`y2, m2, d2, h2, i2`
- jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu konce intervalu,

b1
- je výstupní parametr, do kterého funkce uloží vypočtený počet odbití zvonu #1. Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá výstupní parametr beze změn.

b2
- je výstupní parametr, do kterého funkce uloží vypočtený počet odbití zvonu #2. Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá výstupní parametr beze změn.

návratová hodnota funkce
- bude nastavena na hodnotu 1 pro úspěch (správné vstupní parametry) nebo 0 pro neúspěch (nesprávné vstupní parametry).

Pokud jsou zadané nesprávné vstupní parametry, je potřeba vrátit hodnotu 0 (neúspěch). Správné hodnoty vstupních parametrů musí splňovat:

- rok je větší roven 1600,
- měsíc je platný (1 až 12),
- den je platný (1 až počet dní v měsíci),
- hodina je platná (0 až 23),
- minuta je platná (0 až 59),
- zadaný okamžik počátku intervalu nenastane až po zadaném okamžiku konce intervalu.

Při výpočtu času uvažujeme Gregoriánský kalendář. Tedy měsíce mají vždy 30 nebo vždy 31 dní, výjimkou je únor, který má 28 dní (nepřestupný rok) nebo 29 dní (přestupný rok). Podle Gregoriánského kalendáře platí:

- roky nejsou přestupné,
- s výjimkou let dělitelných 4, které jsou přestupné,
- s výjimkou let dělitelných 100, které nejsou přestupné,
- s výjimkou let dělitelných 400, které jsou přestupné,
- s výjimkou let dělitelných 4000, které nejsou přestupné. Toto pravidlo zatím ještě nikdy neuplatnilo a není zatím oficiálně přijaté. Je to jeden z uvažovaných návrhů, který by Gregoriánský kalendář přiblížil skutečnosti. V naší implementaci jej budeme uvažovat.

Tedy roky 1901, 1902, 1903, 1905, ... jsou nepřestupné (pravidlo 1), roky 1904, 1908, ..., 1996, 2004, ... jsou přestupné (pravidlo 2), roky 1700, 1800, 1900, 2100, ... nejsou přestupné (pravidlo 3), roky 1600, 2000, 2400, ..., 3600, 4400, ... jsou přestupné (pravidlo 4) a roky 4000, 8000, ... nejsou přestupné (pravidlo 5).