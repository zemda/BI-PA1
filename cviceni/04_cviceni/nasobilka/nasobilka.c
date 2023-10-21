#include<stdio.h>

int main(){
    int n = 0, in = 0;

    printf("Rozsah:\n");
    if (scanf("%d", &n) != 1 || (n < 1) || (((in=getchar()) != EOF) && in != ' ' && in!='\n') ){
        printf("Nespravny vstup.\n");
        return 0;
    }

    int digits = 1;
    int temp = n*n;
    while (temp /= 10) digits++;    //Vypocet, kolik má n*n cislic, abych mohl dat dobre odsazeni


    int width = digits;              //šířka svislého popisu, odvíjí se podle toho, kolik má největší číslo cislic, ten popis má např 2 číslice, ale největší číslo 3 = 1 mezera před tím číslem
    int width_body = digits+1;      //šířka těla, té násobilky samotné, největší číslo číslic +1, aby to nebylo na sobě, tzn aby i před tím největším byla jedna mezera
    int num = width_body * (n+1);   //kolik --- musím vyprintit, +1 protože první sloupec
    

    for (int i = n; i > 0; i--){        //print horni rady
        if (i==n) printf("%*c", width_body, '|');
        printf("%*d", width_body, i);
        if (i-1==0) printf("\n");
    }
    
    for (int i = num; i > 1; i--){        //print --+----------
        if (i==num-width) printf("%c", '+');
        printf("%c", '-');
        if (i-1==1) printf("\n");
    }
    
    int x =1;                   //vesměs n-1 sloupců
    for (int i=1; i <= n; i++){ //vertiální/svislé čísla, řádky
        printf("%*d|", width, i);
        
        for (int j = n; j >= x; j--){    //horizontální/vodorovné čísla, sloupce
            printf("%*d", width_body, i*j);
            if (j== x) printf("\n");
        }
        x++;
    }

    return 0;
}