#include<stdio.h>

int main(){
    int x = 0;
    int in = 0;
    printf("ml' nob:\n");
    
    if (scanf(" %d ", &x) != 1 || (x > 9) || (x < 1) || ( ( (in=getchar()) != '\n') && (in != EOF) && (in != ' ') )){
        printf("luj\n");
        return 1;   
    }


    switch(x){
        case 1: printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n"); break;
        case 2: printf("Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n");                                                  break;
        case 3: printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");    break;
        case 4: printf("Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");                                              break;
        case 5: printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");                                     break;
        case 6: printf("Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n");                                                           break;
        case 7: printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");                                            break;
        case 8: printf("Qapla'\nHeghlu'meH QaQ jajvam.\n");                                                                 break;
        case 9: printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");                                             break;
        default:printf("luj\n"); return 1;                                                                                  break;  
    }
    return 0;   
}