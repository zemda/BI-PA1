#include<stdio.h>
#include<stdlib.h>

#define MAX_POSLOUPNOST 2000
#define MAX_POCET_INTERVALU 1999000 //vypocet z funkce interval_count

void interval_count(int n, int* interval_n, int mark); //mark, kdy chci pocitat sumu tech intervalu, coz u pocitani jen kolik ten intervalu-dvojic je nechci - usetri to par ms
int compare_nums(const void* num1, const void* num2);

int posloupnost[MAX_POSLOUPNOST];
int sum_of_intervals[MAX_POCET_INTERVALU];

int compare_nums(const void* num1, const void* num2){ //cppreference
    int a = *(const int*)num1;
    int b = *(const int*)num2;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

void interval_count(int n, int* interval_n, int mark){ //n pocet cisel posloupnosti, interval_n kolik je tech intervalu/nebo dvojic
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++){
            if (mark == 0) for (int k = i; k <= j; k++) sum_of_intervals[*interval_n] += posloupnost[k];
            (*interval_n)++;
        }
    }
}

int main(){
    int n = 0; //pocet cisel posloupnosti
    int interval_n = 0; //pocet intervalu
    int pocet_dvojic = 0;

    printf("Posloupnost:\n");
    while (1){
        if (n > 2000) {printf("Nespravny vstup.\n"); return 1; }
        int ret = scanf("%d", &posloupnost[n]);
        if (ret == EOF) break;
        else if (ret != 1) { printf("Nespravny vstup.\n"); return 1; }
        n++;
    }
    if (n==0) {printf("Nespravny vstup.\n"); return 1;}

    interval_count(n, &interval_n, 0); //pro prvotní výpočet, kolik je intervalů a suma těch intervalů
    qsort(sum_of_intervals, interval_n, sizeof(int), compare_nums);

    int* arr = (int*)malloc(interval_n * sizeof(int));
    int counter = 1, counter2 = 0; //prvni counter na count kolikrat je nejake cislo, counter2 kolik cisel je vice jak 2x
    int elem = sum_of_intervals[0]; //elem, abych poznal, kdy prechazim na jine cislo kdyz jsem v sorted array 11 222 3 44 55 6 7 8 9 10 -> prvne tam je ta 1, az ve 3. iteraci tam bude 2... potrebuju vedet kdy prechazim, abych aktualni counter dal do pole a vynuloval je a zaroven dal counter2++, abych vedel, kolik cisel je vicekrat (nezajima me jake cislo je vicekrat)
    for (int i = 1; i < interval_n; i++){
        if (sum_of_intervals[i] == sum_of_intervals[i-1]) counter++; //kdyz mam stejne 2 cisla, tak ++ 
        if (elem != sum_of_intervals[i]) {
            elem = sum_of_intervals[i]; 
            if (counter > 1) { //pokud byly nejake cisla 2x, tak zapisu kolikrat
                arr[counter2] = counter; counter=1; 
                counter2++;
            }
        }
    }
    for (int i = 0; i < counter2; i++) interval_count(arr[i], &pocet_dvojic, 1);

    free(arr);
    printf("Pocet dvojic: %d\n", pocet_dvojic);

    return 0;   
}