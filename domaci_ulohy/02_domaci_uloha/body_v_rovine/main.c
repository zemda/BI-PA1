#include<stdio.h>
#include<math.h>
#include<float.h>

int eval(double abX, double abY, double abC, double x, double y);
void midEval(double a1, double a2, double b1, double b2, double c1, double c2);

int main(){
    double a1,a2,b1,b2,c1,c2;

    printf("Bod A:\n");
    if (scanf(" %lf %lf", &a1,&a2) != 2 ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf(" %lf %lf", &b1,&b2) != 2 ){
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if (scanf(" %lf %lf", &c1,&c2) != 2 ){
        printf("Nespravny vstup.\n");
        return 1;
    }


    if (((a1 == b1) && (a2 == b2)) || ((a1 == c1) && (a2 == c2)) || ((b1 == c1) && (b2 == c2))){
        printf("Nektere body splyvaji.\n");
        return 0;
    }


    double abX = 0, abY = 0, abC = 0, temp = 0; //ax + by + c = 0
    //AB = B-A
    abX = b1 - a1;
    abY = b2 - a2;
    temp = abX;
    abX = (-1) * abY; //na normalovy vektor
    abY=temp;
    abC = -(abX*a1) - (abY*a2); 


    if (eval(abX, abY, abC, a1, a2) && eval(abX, abY,abC, b1, b2) && eval(abX, abY,abC, c1, c2)){
        printf("Body lezi na jedne primce.\n");
        midEval(a1,a2,b1,b2,c1,c2);
    }else{
        printf("Body nelezi na jedne primce.\n");
    }

    return 0;   
}

int eval(double abX, double abY, double abC, double x, double y){
    double res1;
    abX *= x;
    abY *= y;
    res1 = abX+abY+abC;
    
    double temp = 1;
    if(abX>=abY && abX>=abC) temp = abX;
    if(abY>=abX && abY>=abC) temp = abY;
    if(abC>=abX && abC>=abY) temp = abC;

    if (fabs(res1) <= DBL_EPSILON*temp) return 1;
    else return 0;
}

void midEval(double a1, double a2, double b1, double b2, double c1, double c2){
    char point = 0;
    double a, b, c;
    a = a1 + a2;
    b = b1 + b2;
    c = c1 + c2;
    
    if((b>a && a>c) || (c>a && a>b)) point = 'A';
    if((a>b && b>c) || (c>b && b>a)) point = 'B';
    if((a>c && c>b) || (b>c && c>a)) point = 'C';

    printf("Prostredni je bod %c.\n", point);
}