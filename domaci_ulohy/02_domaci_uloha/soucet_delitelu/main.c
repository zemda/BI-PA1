#include<stdio.h>
#include<math.h>

int isPrime(int num);

int isIdk(int& x){
    x++;
    return 10;
}

int main(){
    

    printf("Intervaly:\n");
    while(1){
        char sign;
        int in, x1 ,x2, sum = 0, quant = 0;


        in=scanf(" %c %d %d", &sign, &x1, &x2);
        if (in==EOF) break;
        if(in != 3 || (sign != '?' && sign != '#') || x1 < 1 || x2 < x1){
            printf("Nespravny vstup.\n");
            return 0;
        }
        
        //? 265 327
        for (int i = x1; i <= x2 && x2 > 0; i++){ //mam cisla napr. 1-10
            int max = sqrt(i);
            for (int j = 1; j <= max; j++){   //to, cim budu delit ty cisla, sqrt cuz pak v else hned sectu prvni a posledni delitel, pak druhy a predposledni, atd
                if (i%j == 0){
                    if (i/j == j) sum += j;
                    else sum += j + i/j;
                }
                
            }
            sum -= i;  //protoze v sume je i to i/x
            if (isPrime(sum)) {
                if (sign == '?') printf("%d\n", i);

                quant++;
                }
            sum = 0;
        }

        printf("Celkem: %d\n", quant);
    }
    
    return 0;   
}

int isPrime(int num){//v teto verzi trocha inspirace z prednasky
    int max;
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    else{
        max = sqrt(num);
        for (int i = 3; i <= max; i+=2){ 
            if (num % i == 0) return 0; //není prvocislo    
        }
    }
    return 1;
}