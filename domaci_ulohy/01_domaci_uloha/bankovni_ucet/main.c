#include<stdio.h>
#include<math.h>


int main(){

    int zustatek = 0;
    double kreditni=0,debetni=0, in=0;
    printf("Zadejte kreditni urok [%%]:\n");
    if (scanf("%lf", &kreditni) !=1 || ((in=getchar())!= ' ' && in != '\n')){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte debetni urok [%%]:\n");
    if (scanf("%lf", &debetni) !=1 || ((in=getchar())!= ' ' && in != '\n')){
        printf("Nespravny vstup.\n");
        return 1;
    }

    int scan=0, days=0, last_day=0, trans=0; double urok=0;

    printf("Zadejte transakce:\n");
    while (1){
        if ((scan=scanf(" %d , %d", &days, &trans)) != 2 || (last_day > days)){
            printf("Nespravny vstup.\n");
            return 1; 
        }

        int x = days-last_day;
        for (int i = 1; i <= x; i++ ){
            if (zustatek > -1) {
                urok = (kreditni/100)*zustatek;
            }
            else {
                urok = (debetni/100)*zustatek;
            }
            zustatek += urok;
        }
        zustatek += (trans*100);
        if (trans == 0) break;
        last_day=days;
        
    }
    printf("Zustatek: %.2f\n", (double)zustatek/100);
    return 0;   
}