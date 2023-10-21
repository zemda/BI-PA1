#include<stdio.h>

int main(){

    printf("Zadejte barvu v RGB formatu:\n");
    unsigned int x,y,z;
    char bracket = {0};
    if (scanf(" rgb ( %u , %u , %u %c ", &x,&y,&z,&bracket) != 4 || (x > 255) || (y > 255) || (z > 255) || (bracket != ')') ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    unsigned int temp1H = 0;
    unsigned int temp2H = 0;
    unsigned int xH = 0;
    unsigned int yH = 0;
    unsigned int zH = 0;

    if (x != 0){ 
        temp1H = x/16;
        temp2H = ((double)x/16-temp1H)*(double)16;
        xH = (temp1H << 4) + (temp2H); //nebo 16* temp1H + temp2H
    }
    if (y!=0){
        temp1H = y/16;
        temp2H = ((double)y/16-temp1H)*(double)16;
        yH = (temp1H << 4) | (temp2H);
    }
    if (z != 0){
        temp1H = z/16;
        temp2H = ((double)z/16-temp1H)*(double)16;
        zH = (temp1H << 4) | (temp2H);
    }
    printf("#%02X%02X%02X\n",xH,yH,zH);

    return 0;
}