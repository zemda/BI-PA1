# Řazení spojového seznamu II


Úkolem je realizovat sadu funkcí (ne celý program, jen funkce) pro práci se spojovými seznamy. Funkce umožní seznam snadno vytvářet, mazat a řadit. Úloha je rozšířením jednoduššího zadání, přidává možnost vlastního komparátoru. Doporučujeme nejprve vyřešit zadání jednodušší a to pak rozšiřovat.

Pří řešení problému se setkáte s následujícími deklaracemi:

`TITEM`  
Tato struktura reprezentuje prvek jednosměrně zřetězeného spojového seznamu. Deklarace struktury je pevně daná v testovacím prostředí, Vaše implementace bude tuto nezměněnou deklaraci používat (nemůže/nesmí ji měnit). Ve struktuře jsou následující složky:
- `m_Next` ukazatel na další prvek ve spojovém seznamu, hodnota NULL pro poslední prvek,
- `m_Name` řetězec s názvem prvku seznamu,
- `m_Secret` tajná data přičleněná k této položce seznamu. Vaše implementace s touto složkou nepotřebuje pracovat a nesmí ji měnit (výjimkou je inicializace ve funkci newItem).
```c
TITEM * newItem ( const char * name, TITEM * next )
```
- Tato funkce vytvoří nový záznam TITEM. Paměť pro strukturu budete alokovat dynamicky. Funkce navíc zkopíruje jméno a odkaz na další prvek z parametrů do složek m_Next a m_Name. Složku m_Secret funkce vyplní nulovými bajty ('\0'). Návratovou hodnotou funkce je ukazatel na takto vytvořenou a inicializovanou struktury TITEM. Implementace funkce je Vaším úkolem.

```c
void freeList ( TITEM * l )
```
- Funkce slouží k pohodlnému výmazu spojového seznamu. Parametrem je počátek mazaného spojového seznamu l. Funkce zajistí uvolnění všech prostředků, které seznam zabíral. Implementace funkce je Vaším úkolem.

```c
TITEM * sortListCmp ( TITEM * l, int ascending, int (*cmp)(const TITEM *, const TITEM *) )
```
- Funkce slouží k seřazení prvků ve spojovém seznamu. Parametrem je počátek řazeného spojového seznamu l, požadované seřazení ascending a komparátor cmp. Funkce zajistí přeskupení prvků v zadaném seznamu tak, aby pořadí vyhovovalo požadovanému uspořádání. Funkce nesmí prvky původního seznamu uvolňovat (a např. vrátit jejich nově vytvořenou kopii). Naopak, musí přepojit odkazy existujících prvků a vrátit ukazatel na první prvek takto vzniklého seznamu
- Kritériem pro řazení je výsledek po zavolání komparátoru cmp. Vždy, když je potřeba určit vzájemné uspořádání dvou prvků, zavolá řadící algoritmus funkci předanou parametrem cmp Volání komparátoru pracuje stejně jako v knihovní funkci qsort - vrací zápornou / nulovou / kladnou hodnotu, pokud byl první parametr předaný komparátoru menší / stejný / větší než parametr druhý. Řazení dále ovlivní směr uspořádání - buď je vzestupné (parametr ascending není nula) nebo sestupné (parametr ascending je roven nule). Funkce musí zajistit, že řazení je stabilní.