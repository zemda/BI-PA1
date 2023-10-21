#include<stdio.h>

int main(){
    unsigned int t1h,t1m,t1s,t1ms;
    unsigned int t2h,t2m,t2s,t2ms;
    int digits1 = 0;
    int digits2 = 0;
    //Neoptimalni trash

    //Casy nesmi byt vetsi jak 23h, 59m, 59s, 999ms 
    printf("Zadejte cas t1:\n");
    if(scanf(" %u : %u : %u ",&t1h,&t1m,&t1s)!=3 || (t1h > 23) || (t1m > 59) || (t1s > 59)){
        printf("Nespravny vstup.\n");
        return 1;
    }
    if (scanf(",%u%n", &t1ms, &digits1) != 1 || t1ms>999){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte cas t2:\n");
    if(scanf(" %u : %u : %u ",&t2h,&t2m,&t2s)!=3 || (t2h > 23) || (t2m > 59) || (t2s > 59)){
        printf("Nespravny vstup.\n");
        return 1;
    }
    if ((scanf(",%u%n", &t2ms, &digits2) != 1) || (t2ms>999)){
        printf("Nespravny vstup.\n");
        return 1;
    }

    switch (digits1){
        case 2:
            t1ms *= 100;
            break;
        case 3:
            t1ms *= 10;
            break;
        default:
            break;
    }
    switch (digits2){
        case 2:
            t2ms *= 100;
            break;
        case 3:
            t2ms *= 10;
            break;
        default:
            break;
    }


    //Osetreni vetsiho casu 1 nez 2
    unsigned int x1Ms = (t1h*60*60*1000 + t1m*60*1000 + t1s*1000 + t1ms); 
    unsigned int x2Ms = (t2h*60*60*1000 + t2m*60*1000 + t2s*1000 + t2ms);
    if (x1Ms > x2Ms){        
        printf("Nespravny vstup.\n");
        return 1;
    }

    //Vypocet vysledku
    unsigned int resultMs = x2Ms - x1Ms;
    unsigned int resultH = (double)resultMs/1000/60/60;
    resultMs -= resultH*60*60*1000;
    unsigned int resultM = (double)resultMs/1000/60;
    resultMs -= resultM*60*1000;
    unsigned int resultS = (double)resultMs/1000;
    resultMs -= resultS*1000;


    printf("Doba: %2u:%02u:%02u,%03u\n", resultH, resultM,resultS, resultMs);

    return 0;
}