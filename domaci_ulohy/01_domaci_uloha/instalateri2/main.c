#include<stdio.h>
#include<math.h>

int point_val(int x, int y, int z, int a);
int side_eval(int x, int y, int z, int a);
int calc_pipe(int p1, int p2, int x1, int y1, int z1, int x2, int y2, int z2, int a, int *a1, int *b1, int *d1, int *d2);
double calc_hose(int a, int b);
int return_max(int l1, int l2, int l3, int l4);
int ret_max_a(int a, int b, int c, int d, int e, int f, int g, int h);

int main(){
    int a1=0, b1=0,c=0,d=0;
    int a, x1, y1, z1, x2, y2, z2;//, in;

    printf("Rozmer mistnosti:\n");
    if ( scanf(" %d", &a) != 1 || (a < 1)){// ||( ((in=getchar()) != '\n') && (in != ' ' ) )){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod #1:\n");
    if ( (scanf(" %d %d %d", &x1, &y1, &z1)) != 3 || (point_val(x1,y1,z1,a))){// || ((in=getchar()) != '\n' && (in != ' ')  )){
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
    pipe = calc_pipe(p1, p2, x1, y1, z1, x2, y2, z2, a,&a1,&b1,&c,&d);

    if (c!=0 && d!=0) hose=calc_hose(c,d);
    else hose = calc_hose(a1,b1);
    
    printf("Delka potrubi: %d\n", pipe);
    printf("Delka hadice: %f\n", hose);
    return 0;   
}

int calc_pipe(int p1, int p2, int x1, int y1, int z1, int x2, int y2, int z2, int a, int *a1, int *b1, int *d1, int *d2){
    int length = 0, num = 0;
    int intern_p1 = 0, intern_p2 = 0;
    int c, v, b, n, m, f, g, h;

    switch (p1){
        case 3: intern_p1 = 1; break;
        case 2: intern_p1 = 10; break;
        case 1: intern_p1 = 20; break;
        case 4: intern_p1 = 35; break;
        case 5: intern_p1 = 200; break;
        case 6: intern_p1 = 100; break;
    }
    switch (p2){
        case 3: intern_p2 = 1; break;
        case 2: intern_p2 = 10; break;
        case 1: intern_p2 = 20; break;
        case 4: intern_p2 = 35; break;
        case 5: intern_p2 = 200; break;
        case 6: intern_p2 = 100; break;
        default: break;
    }

    int xy = intern_p1 + intern_p2;
    int l1, l2, l3, l4;
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
    case 21:     //stena 3, if blizsi pres stenu 2 a 1 nebo 4 a 1, A NEBO PRES STROP/podlahu
        l1 = *a1 + abs(x1+y2+x2);
        l2 = *a1 + (abs(a-x1) + abs(x2-a) + y2);
        l3 = ((a-z1) + a + (a-z2)) + abs(x1-x2);//stena 3, strop, 1
        l4 = (z1+z2 + a + abs(x1-x2));//stena 3, podlaha, 1 
        num = return_max(l1, l2, l3, l4);

        if (num == 1 ){*b1 = abs(x1+y2+x2);}
        else if (num == 2 ){*b1 = (abs(a-x1) + abs(x2-a) + y2);}
        else if (num == 3 ){*a1 = (((a-z1) + a + (a-z2))); *b1 = abs(x1-x2);}
        else {*a1 = (z1+z2 + a + abs(x1-x2)); *b1 = abs(x1-x2);}

        length = *a1 + *b1;
        break;
    case 45:    //nebo stena 2 do 4, pres 34 / 14
        l1 = *a1 + ((a-y1) + x2 + (a-y2));
        l2 = *a1 + (y1 + x2 + y2);
        l3 = ((a-z1) + a + (a-z2)) + abs(y1-y2);//stena 2, strop, 4
        l4 = ((z1+z2 + a) + abs(y1-y2));//stena 2, podlaha, 4
        
        c = *a1; v = ((a-y1) + x2 + (a-y2));
        b = *a1; n = (y1 + x2 + y2);
        m = ((a-z1) + a + (a-z2)); f = abs(y1-y2);
        g = (z1+z2 + a); h = abs(y1-y2);

        num = ret_max_a(c,v,b,n,m,f,g,h);
        if (num == 1) {*d1 = c; *d2 = v; }
        else if (num == 2) {*d1 = b; *d2 = n; }
        else if (num == 3) {*d1 = m; *d2 = f; }
        else {*d1 =g; *d2 = h; }
        
        num = return_max(l1, l2, l3, l4);
        if (num == 1 ){*b1 = ((a-y1) + x2 + (a-y2));}
        else if (num == 2 ){*b1 = (y1 + x2 + y2);}
        else if (num == 3 ){*a1 = (((a-z1) + a + (a-z2))); *b1 = abs(y1-y2);}
        else {*a1 = z1+z2+a; *b1 = abs(y1-y2);}

        length = *a1 + *b1;
        break;
    case 2: case 40: // ve stejne stene
        *b1 = abs(x1-x2);
        length = *a1 + *b1;
        break;
    case 20: case 70: //je to ve stejne stene
        *b1 = abs(y1-y2);
        length = *a1 + *b1;
        break;
    case 200: case 400: //ve stejne stene, podlaha, strop
        *a1 = abs(x1-x2);
        *b1 = abs(y1-y2);
        length = *a1 + *b1;
        break;
    case 201: case 101:
        if (intern_p1 > intern_p2){ //if true, tak bod 1 je nalevo, teda prvni bod je strop, druhy strana 3
            *b1 = abs(a-y1) + abs(z1-z2); //strop ke strane 3 + vyska
            *a1 = abs(x2-x1);
        }else{ 
            *b1 = abs(z1-z2) + abs(a-y2);
            *a1 = abs(x2-x1);
        }
        length = *a1 + *b1;
        break;
    case 210: case 110:
        if (intern_p1 > intern_p2){ //if true, tak bod 1 je nalevo, teda prvni bod je strop, druhy strana 2
            *b1 = x1 + abs(z1-z2); //strop ke strane 3 + vyska
            *a1 = abs(y2-y1);
        }else{ 
            *a1 = abs(z1-z2) + x2;
            *b1 = abs(x2-x1);
        }
        length = *a1 + *b1;
        break;
    case 220: case 120:
        if (intern_p1 > intern_p2){ //if true, tak bod 1 je nalevo, teda prvni bod je strop, druhy strana 1
            *b1 = abs(y1) + abs(z1-z2); //strop ke strane 3 + vyska
            *a1 = abs(x2-x1);
        }else{ 
            *a1 = abs(z1-z2) + abs(y2);
            *b1 = abs(x2-x1);
        }
        length = *a1 + *b1;
        break;
    case 235: case 135:
        if (intern_p1 > intern_p2){ //if true, tak bod 1 je nalevo, teda prvni bod je strop, druhy strana 4
            *b1 = abs(a-x1) + abs(z1-z2); //strop ke strane 3 + vyska
            *a1 = abs(y2-y1);
        }else{ 
            *a1 = abs(z1-z2) + abs(a-x2);
            *b1 = abs(x2-x1);
        }
        length = *a1 + *b1;
        break;
    case 300: //strop + podlaha
        l1 = (a + y1 + y2) + (abs(x2-x1)); //a + b, //pres stranu 1, a misto z1-z2, cuz je to max(a)-0
        l2 = (a + x1 + x2) + (abs(y1-y2));
        l3 = (a+ (a-y1) + (a-y2)) + (abs(x2-x1));
        l4 = (a+ (a-x1) + (a-x2)) + (abs(y1-y2));
        //int c, v, b, n, m, f, g, h;
        c = (a + y1 + y2); v = (abs(x2-x1));
        b = (a + x1 + x2); n = (abs(y1-y2));
        m = (a+ (a-y1) + (a-y2)); f = (abs(x2-x1));
        g = (a+ (a-x1) + (a-x2)); h = (abs(y1-y2));

        num = ret_max_a(c,v,b,n,m,f,g,h);
        if (num == 1) {*d1 = c; *d2 = v; }
        else if (num == 2) {*d1 = b; *d2 = n; }
        else if (num == 3) {*d1 = m; *d2 = f; }
        else {*d1 =g; *d2 = h; }

        num = return_max(l1, l2, l3, l4);
        if (num == 1 ){*a1 = (a + y1 + y2); *b1 = (abs(x2-x1));}
        else if (num == 2 ){*a1 = (a + x1 + x2); *b1 = (abs(y1-y2));}
        else if (num == 3 ){*a1 = (a+ (a-y1) + (a-y2)); *b1 = (abs(x2-x1));}
        else {*a1 = (a+ (a-x1) + (a-x2)); *b1 = (abs(y1-y2));}

        length = *a1 + *b1;
        break;
    default: break;
    }
    return length;
}
int ret_max_a(int a, int b, int c, int d, int e, int f, int g, int h){
    double r1, r2, num, x;
    double a1,a2,a3,a4;
    a1=(sqrt(((double)a*a) + ((double)b*b)));
    a2=(sqrt(((double)c*c) + ((double)d*d)));
    a3=(sqrt(((double)e*e) + ((double)f*f)));
    a4=(sqrt(((double)g*g) + ((double)h*h)));
    r1 = (a1 < a2) ? a1 : a2;
    r2 = (a3 < a4) ? a3 : a4;
    if (r1 < r2 ) x = 12;
    else x = 34;
    if (x == 12) num = (a1 < a2) ? 1 : 2;
    else num = (a3 < a4) ? 3 : 4;
    return num;
}
int return_max(int l1, int l2, int l3, int l4){
    int r1, r2, num, x;
    r1 = (l1 < l2) ? l1 : l2;
    r2 = (l3 < l4) ? l3 : l4;
    if (r1 < r2 ) x = 12;
    else x = 34;
    if (x == 12) num = (l1 < l2) ? 1 : 2;
    else num = (l3 < l4) ? 3 : 4;
    return num;
}
double calc_hose(int a1, int b1){
    double length = 0;
    length = sqrt(((double)a1*a1) + ((double)b1*b1));
    return length;
}
int side_eval(int x, int y, int z, int a){
    int side=0;
    if (z==a){
        side = 5; //strop
    }else if (z==0){
        side = 6; //podlaha
    }else if (y==0){
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
    if ( ((x < 20 && y < 20) || (x > a || y > a)) || ((x > a-20) && (y < 20)) || ((y > a-20) && (x < 20)) || (z>a) || (x < 0) || (y < 0) || (x < 20 && ((z==0) || z==a)) || (y < 20 && ((z==0) || z==a)) ){//mozna jeste Z v rohu, idk, dodelat ty rohy nejak
        //printf("x");
        return 1;                                                                               //jeste podminky pro z = a/ z=0, coz je ok
    }else if ( ((y!=0 && x !=0 && (z!=a && z!= 0)) && (x!=a && y!=a) && (z!=a && z!= 0) )){ //bod neni ve stene, ale nekde uprostred
        //printf("x1");
        return 1;
    }
    
    return 0;
}