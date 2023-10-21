#include<stdio.h>
#include<math.h>

int point_val(int x, int y, int z, int a);
int side_eval(int x, int y, int z, int a);
int calc_pipe(int p1, int p2, int x1, int y1, int z1, int x2, int y2, int z2, int a, int *a1, int *b1);
double calc_hose(int a, int b);



int main(){
    int a1, b1;

    int a, x1, y1, z1, x2, y2, z2;//, in;

    printf("Rozmer mistnosti:\n");
    if ( scanf(" %d", &a) != 1 || (a < 1)){// ||( ((in=getchar()) != '\n') && (in != ' ' ) )){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod #1:\n");
    if ( scanf(" %d %d %d", &x1, &y1, &z1) != 3 || (point_val(x1,y1,z1,a))){// || ((in=getchar()) != '\n' && (in != ' ')  )){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod #2:\n");
    if ( scanf(" %d %d %d", &x2, &y2, &z2) != 3 || point_val(x2,y2,z2,a)){// ||((in=getchar()) != '\n' && in != ' ' && in != EOF )){
        printf("Nespravny vstup.\n");
        return 1;
    }

    int pipe = 0;
    double hose = 0;

    int p1, p2;

    p1 = side_eval(x1,y1,z1,a);
    p2 = side_eval(x2,y2,z2,a);


    pipe = calc_pipe(p1, p2, x1, y1, z1, x2, y2, z2, a,&a1,&b1);
    hose = calc_hose(a1,b1);
    
    
    printf("Delka potrubi: %d\n", pipe);
    printf("Delka hadice: %f\n", hose);
    

    return 0;   
}

int calc_pipe(int p1, int p2, int x1, int y1, int z1, int x2, int y2, int z2, int a, int *a1, int *b1){
    int length = 0;
    int intern_p1 = 0, intern_p2 = 0;
    //printf("p1 %d, p2 %d\n", p1, p2);

    switch (p1){
        case 3: intern_p1 = 1; break;
        case 2: intern_p1 = 10; break;
        case 1: intern_p1 = 20; break;
        case 4: intern_p1 = 35; break;
    }

    switch (p2){
        case 3: intern_p2 = 1; break;
        case 2: intern_p2 = 10; break;
        case 1: intern_p2 = 20; break;
        case 4: intern_p2 = 35; break;
        default: break;
    }

    
    int xy = intern_p1 + intern_p2;
    int l1, l2;//, l3, l4;
    *a1 = abs(z1-z2);
    switch (xy){
    case 11: 
        if (intern_p1 < intern_p2){
            *b1 = abs(a-y1) + x2;
        }else{
            *b1 = x1 + abs(a-y2);
        }
        length = *a1 + *b1;
        break;
    case 30: 
        if (intern_p1 < intern_p2){
            *b1 = y1+x2;

        }else{
            *b1 = x1+y2;
        }
        length = *a1 + *b1;
        break;
    case 55: //steny vedle sebe, 32 21 14
        if (intern_p1 < intern_p2){ //if true, tak bod 1 je nalevo, else napravo
            *b1 = abs(a-x1) + y2;
            
        }else {
            *b1 = y1 + abs(a-x2);
        }
        length = *a1 + *b1;
        break;
    case 36:    //stena vedle sebe, 43, takze kdyz stena 4 = 35 je nalevo
        if (intern_p1 > intern_p2){ //if true, tak bod 1 je nalevo, else napravo
            *b1 = abs(a-y1) + abs(a-x2);
            length = *a1 + *b1;
        }else {
            *b1 = abs(a-x1) + abs(a-y2);
            length = *a1 + *b1;
        }
        break;
    case 21:     //stena 3, if blizsi pres stenu 2 a 1 nebo 4 a 1, 
        l1 = *a1 + abs(x1+y2+x2);
        l2 = *a1 + abs(a-x1) + abs(x2-a) + y2;
        length = (l1 < l2) ? l1 : l2;
        *b1 = (l1 < l2) ? abs(x1+y2+x2): (abs(a-x1) + abs(x2-a) + y2);
        break;
    case 45:    //nebo stena 2 do 4, pres 34 / 14
        l1 = *a1 + ((a-y1) + x2 + (a-y2));
        l2 = *a1 + y1 + x2 + y2;
        length = (l1 < l2) ? l1 : l2;
        *b1 = (l1 < l2) ? ((a-y1) + x2 + (a-y2)): (y1 + x2 + y2);
        break;
    case 2: case 40: // ve stejne stene
        *b1 = abs(x1-x2);
        length = *a1 + *b1;
        break;
    case 20: case 70: //je to ve stejne stene
        
        *b1 = abs(y1-y2);
        length = *a1 + *b1;
        break;
    default: break;
    }


/*
    switch (p1){
    case 1:
        switch (p2){
        case 1:
            a1 = abs(z1-z2);
            b1 = abs(x1-x2);
            length = a1+b1;
            break;
        case 2:
            a1 = abs(z1-z2);
            b1 = abs(x1-y2);
            length = a1 + b1;
            break;
        case 3:
            int l1, l2;
            a1 = abs(z1-z2);
            l1 = a1 + abs(x1+y2+x2);
            l2 = a1 + abs(a-x1) + x2 + y2;
            length = (l1 > l2) ? l1 : l2;
            b1 = (l1 > l2) ? abs(x1+y2+x2): (x2 + y2);
            break;
        case 4:
            a1 = abs(z1-z2);
            b1 = abs(a-x1) + x2;
            length = a1 + b1;
            break;
        default:
            break;
        }

        break;
    case 2:

        break;
    case 3:
        break;
    case 4:
        break;


    default:
        break;
    }*/



    return length;
}

double calc_hose(int a1, int b1){
    double length = 0;
    //printf("a1 %d, b1 %d\n", a1, b1);
    length = sqrt(((double)a1*a1) + ((double)b1*b1));

    return length;
}

int side_eval(int x, int y, int z, int a){
    int side=0;
    if (y==0){
        side = 1;
    }else if (x==0){
        side = 2;
    }else if (y==a){
        side = 3;
    }else if (x==a){
        side = 4;
    }
    return side;
}



int point_val(int x, int y, int z, int a){
        //                          kdyz je souradka 10 300 100, tak 0 300 100 je valid, ale 10 neni 20 daleko od zdi
    if ( ((x < 20 && y < 20) || (x > a && y > a)) || (z < 20 || z >= a ) || ((x > a-20) && (y < 20)) || ((y > a-20) && (x < 20)) ){//mozna jeste Z v rohu, idk, dodelat ty rohy nejak
        //printf("x");
        return 1;
    }else if ( ((y!=0 && x !=0) && (x!=a && y!=a))){ //bod neni ve stene, ale nekde uprostred
        //printf("x1");
        return 1;
    }
    
    

    //if ((x < 20 || x > a) || (y < 20 || y > a) || (z < 20 || z >= a ) || ((x > a-20) && (y != 0)) || ((y > a-20) && (x != 0)) )
    //( ((y!=0 && x !=0) && (x!=a && y!=a)))
    // if (((x < 20) && (y < 20)) || ((x < 20) && (x > 0)) || ((y < 20) && (y > 0)) || (z < 20) || ((x > a-20) && (y != 0)) || ((y > a-20) && (x != 0)) || (z>=a)){
    return 0;
}