#include<stdio.h>
#include<math.h>

int main(){
    double a,b,c, res;
    char sign;

    printf("Zadejte rovnici:\n");
    if(scanf(" %lf %c %lf = %lf", &a, &sign, &b, &c) != 4){
        printf("Nespravny vstup.\n");
        return 1;
    } 

    switch (sign){
    case '+': res = a + b; break;
    case '-': res = a - b; break;
    case '*': res = a * b; break;
    case '/':
        if (b==0) {printf("Nespravny vstup.\n"); return 1; break;}
        
        double r; int xy;
        r = fmod(a,b);
        if (r < 10e-7 && r >= 0) res = a / b;
        else {xy = a/b; res = xy;}
        
        
        break;
    default: printf("Nespravny vstup.\n"); return 1; break;
    }

    if (fabs(res - c) <= fabs(res * 1e-6)) printf("Rovnice je spravne.\n");
    else printf("%g != %g\n", res, c);
    
    return 0;   
}