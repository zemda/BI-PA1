#include<stdio.h>

void outer_border(int num);
void chessboard(int wh_size, int field_size);


int main(){

    int wh_size, field_size, in;
    printf("Zadejte pocet poli:\n");
    if (scanf("%d", &wh_size) != 1 || (wh_size < 1) || (((in=getchar()) != ' ') && (in != '\n' ))){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte velikost pole:\n");
    if (scanf("%d", &field_size) != 1 || (field_size < 1) || (((in=getchar()) != ' ') && (in != '\n' ) && (in != EOF))){
        printf("Nespravny vstup.\n");
        return 1;
    }


    int total_size = wh_size * field_size + 2;
    outer_border(total_size);           //venkovní horní ohraničení
    chessboard(wh_size, field_size);    //"hrací" plocha
    outer_border(total_size);           //venkovní spodní ohraničení


    return 0;
}

void chessboard(int wh_size, int field_size){

    for (int i=1; i < wh_size+1; i++){ //cyklus pro všechny řádky, bez těch horních okrajů, = -2 +1 (protoze i=1)
        
        char C_field = ' ';     //znak, který se má dát do šachovnice - '0' nebo 'X'
        int sw = 1;             //promenna, pomoci ktere se prepina ten znak C_field
        int x = i;              //pomocna promena pro odd/even řádek, protože začínající X jsou vždy even
        
        //C_field = (sw % 2 == 0) ? 'X':' ';
        
        for (int l=0; l < field_size; l++){ // cyklus pro řádek * field size, takže jakoby pro celý jeden řádek
           
            if (x % 2 == 0) sw = 2;     //Pokud je sudý řádek, tak chceme začínat s X
            else sw = 1;                //Pokud je lichý řádek, chceme začínat mezerou

            for (int j=0; j < wh_size+2; j++){ //print jednotlivých znaků v řádku
                
                if (j==0) printf("|");                  //ohraničení zleva
                else if (j == wh_size+1) printf("|\n"); //ohraničení zprava
                else {                                  //vnitřek mezi ohraničením
                    C_field = ((sw=sw % 2) == 0) ? 'X':' '; //přepnutí z jednoho znaku na druhý
                    sw++;
                    for (int k=0; k < field_size; k++){ //print jednoho pole Xek nebo mezer, část jednoho řádku - Field_size krát mezera/x
                        printf("%c", C_field);
                    }
                }
            }
        }
    }
}


void outer_border(int num){ //venkovní horní a spodní ohraničení
    
    for (int i=0; i < num; i++){
        if (i == 0) printf("+");
        else if (i == num-1) printf("+\n");
        else printf("-");
    }
}