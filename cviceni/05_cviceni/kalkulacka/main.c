#include<stdio.h>
#include<math.h>

int main(){
    double x1,x2,res;
    char sign;

    printf("Zadejte vzorec:\n"); 

    //melo by fungovat, misto char equals jsem tu dal ten =, predtim jsem na to zapomnel xd
    if (scanf(" %lf %c %lf =", &x1,&sign,&x2) != 4){
        printf("Nespravny vstup.\n");
        return 1;
    }

    switch (sign){
    case '+': res = x1 + x2; break;
    case '-': res = x1 - x2; break;
    case '*': res = x1 * x2; break;
    case '/':
        if (x2 == 0){printf("Nespravny vstup.\n"); return 1; break;} 
        double r; int xy;
        r = fmod(x1,x2);
        if (r < 10e-7 && r >= 0) res = x1 / x2;
        else {xy = x1/x2; res = xy;}
        break;
    default: printf("Nespravny vstup.\n"); return 1; break;
    }

    printf("%g\n", res);
    return 0;   
}