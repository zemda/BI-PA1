#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define ARRAY_SIZE 10000

int bells (int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, long long int * b1, long long int * b2 );
int validateDate(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, int* sundays, int* leap_count_year1, int* leap_count_year2);
int daysInMonth(int month, int year);
int isLeap(int year);
int convertMonthToDay(int month, int year);
int ret12hrs(int h);
void fillInLeaps(int array[]);
int weekday(int d, int m, int y);
int leapYears[ARRAY_SIZE] = {0}; //global cuz idk jestli muzu menit parametry funkce, je to memory w;aste, ale stejne nemuzu asi menit main
int is_filled = 0; //cuz v progtestu neni muj main, kde to jednou spustim


int bells ( int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, long long int * b1, long long int * b2 ){
    printf("%d, %d, %d, %d, %d\n", y1,m1,d1,h1, i1);
    printf("%d, %d, %d, %d, %d\n", y2,m2,d2, h2, i2);
    if (is_filled!=1) fillInLeaps(leapYears);
    
    
    int numberOfSundays = 0; //jsou to nedele mezi temi terminy, 1 ale muze chybet, kdyz je druhy termin nedele
    int leap_count_year1 = 0; //in the end to nevadilo, cuz jsem to nemel u ani jednoho, takze by se to stejne odecetlo, ale mohlo to delat problemy s nedelema
    int leap_count_year2 = 0; //kolik je dnu navic, kolik jich mam pricist, cuz jsem nasobil y1*365, ale chybely mi ty prestupne roky
    if(!validateDate(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2, &numberOfSundays, &leap_count_year1, &leap_count_year2)) return 0; 
        
    int convertedM1 = convertMonthToDay(m1, y1);
    int convertedM2 = convertMonthToDay(m2, y2);
    long long int interval1 = ((long long int)y1*365 + convertedM1 + d1 + leap_count_year1)*24*60 + (h1 * 60) + (i1); //v minutach
    long long int interval2 = ((long long int)y2*365 + convertedM2 + d2 + leap_count_year2)*24*60 + (h2 * 60) + (i2); //v minutach
    long long int interval = interval2 - interval1; //mam celkvoy pocet minut

    int je_nedele_prvni_datum = weekday(d1, m1, y1);
    int je_nedele_druhy_datum = weekday(d2, m2, y2);
    
    if (interval != 0){
        if (je_nedele_druhy_datum == 0 && je_nedele_prvni_datum == 0 && interval < 1439){
            *b1 = 0;
            *b2 = 0;
            return 1;
            }//1439 = 23h + 59min
        if (je_nedele_prvni_datum == 0) { 
                if (i1 != 0)  {interval = interval - (((24-h1)-1)*60) - (60-i1);}
                else {interval = interval - ((24-h1)*60) - i1; }
                if (numberOfSundays > 0) numberOfSundays--;
        }
        if (je_nedele_druhy_datum == 0) { interval = interval - (h2*60) - i2;}
        interval = interval - (numberOfSundays*24*60);
    }else if (interval == 0 && je_nedele_prvni_datum == 0 && je_nedele_druhy_datum == 0){
        *b1 = 0;
        *b2 = 0;
        return 1;
    }
       
    //za cely den/dny 
    long long int celeDny = interval/60/24;
    long long int bell1 = 240 * celeDny;
    long long int bell2 = 156 * celeDny;

    long long int meziIntervalMinuty = interval - (celeDny*60*24); //odecist ty cele dny
    long long int meziIntervalHodiny = meziIntervalMinuty/60; ////Hodinovy zvon za zbytkove hodiny, co netvori den, ale jsou 
    printf("cele dny %lld, interval %lld, meziMinuty %lld, meziHodiny %lld\n",celeDny, interval, meziIntervalMinuty, meziIntervalHodiny);
    
    //Bell 2, nefunguje moc dobre
    int origH1 = h1;
    if (je_nedele_prvni_datum == 0 && je_nedele_druhy_datum!=0) {h1=0; meziIntervalHodiny++;}
    else if (i1 != 0) h1++;
    if (((i1==0 && i2 == 0) || (i1==0 && i2!=0)) && je_nedele_prvni_datum!=0 && je_nedele_druhy_datum!=0) meziIntervalHodiny++;
    if ((i1 != i2 && h2 > origH1 && meziIntervalHodiny==0)) {meziIntervalHodiny++;}
    for (int i = 0; i < meziIntervalHodiny; i++){

        bell2 += ret12hrs(h1);
        //printf("%d, ", h1);
        if (h1 == 24) h1 = 1;
        else h1++;

    }

    //Bell 1, tedy minutovej, mel by asi 100% fungovat afaik, //meziinterval rika, kolikrat to protocit
    long long int celeHodiny = meziIntervalMinuty/60; //znovu ty celé hodiny, cuz je nahore v intervalu odcitam
    meziIntervalMinuty -= (celeHodiny*60); //od minut odečtu ty hodiny, které o radek niz uz vynasobim odbitim
    bell1 += 10*celeHodiny; //10 je kolikrat odbije za celou hodinu, coz udelam tak a v cyklu jen zbytky
    
    if (je_nedele_prvni_datum == 0) i1 = 0; //protoze musi zvonit hned o pulnoci, kdyz je prvni den intervalu nedele
    meziIntervalMinuty = meziIntervalMinuty / 15;

    if ( (i1 % 15 == 0|| i2 % 15 == 0) && je_nedele_druhy_datum != 0) meziIntervalMinuty++;

    for (int i = 0; i < meziIntervalMinuty; i++){
        if (i1 > 0 && i1 < 15) i1 = 15;
        else if (i1 > 15 && i1 < 30) i1 = 30;
        else if (i1 > 30 && i1 < 45) i1 = 45;
        else if (i1 > 45) i1 = 0;

        switch (i1){
        case 0: bell1 += 4; break;
        case 15: bell1 += 1; break;
        case 30: bell1 += 2; break;
        case 45: bell1 += 3; break;
        default: break;}
        i1 += 15;
    }

   printf("bell1: %lld, ", bell1); printf("bell2: %lld\n", bell2);
   printf("je_nedele_prvni_datum %d, je_nedele_druhe_datum %d, count %d\n", je_nedele_prvni_datum, je_nedele_druhy_datum, numberOfSundays);
   printf("\n");
   *b2 = bell2;
   *b1 = bell1;
   return 1;
}




#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

    assert ( bells ( 1600, 1, 1,  0,  0,
                     4000, 1, 1,  0,  0, &b1, &b2 ) == 1);

  //printf("\n\n\n\n");

        //printf("b1: %lld, b2: %lld\n", b1, b2);

assert ( bells ( 2022, 11, 1,  10,  25,
                   2022, 11, 1,  11,  0, &b1, &b2 ) == 1
            && b1 == 9
            && b2 == 11);


  assert ( bells ( 2022, 11, 1,  10,  20,
                   2022, 11, 1,  11,  10, &b1, &b2 ) == 1
            && b1 == 9
            && b2 == 11);



 assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
           
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
        
  assert ( bells ( 2100, 12, 31,  0,  0,
                   2100, 12, 31,  0,  0, &b1, &b2 ) == 1 
          && b1 == 4
          && b2 == 12);
  assert ( bells ( 2000, 1, 1,  23,  69,
                   2000, 1, 2,  23,  59, &b1, &b2 ) == 0 
          && b1 == 4
          && b2 == 12);
        
        
  assert ( bells ( 2022, 10, 16,  0,  0,
                   2022, 10, 23,  0,  0, &b1, &b2 ) == 1 
          && b1 == 1440
          && b2 == 936);

  assert ( bells ( 2022, 10, 17,  0,  0,
                   2022, 10, 23,  0,  0, &b1, &b2 ) == 1 
          && b1 == 1440
          && b2 == 936);

  assert ( bells ( 2022, 10, 16,  0,  0,
                   2022, 10, 22,  23,  45, &b1, &b2 ) == 1 
          && b1 == 1440
          && b2 == 936);

  assert ( bells ( 2022, 10, 17,  0,  0,
                   2022, 10, 22,  23,  45, &b1, &b2 ) == 1 
          && b1 == 1440
          && b2 == 936);
          
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

void fillInLeaps(int array[]){
    for (int i=0; i < ARRAY_SIZE; i++){
        if (isLeap(i)) array[i] = 1;
        else array[i] = 0;
    }
    is_filled = 1;
}

int ret12hrs(int h){
    switch (h){
    case 0: return 12; break;
    case 13: return 1; break;
    case 14: return 2; break;
    case 15: return 3; break;
    case 16: return 4; break;
    case 17: return 5; break;
    case 18: return 6; break;
    case 19: return 7; break;
    case 20: return 8; break;
    case 21: return 9; break;
    case 22: return 10; break;
    case 23: return 11; break;
    case 24: return 12; break;
    default: return h; break;}
    return 0;
}

int weekday(int d, int m, int y){
    int weekdayy;
    if (y>=4000) weekdayy = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400 - y*4000)%7; 
    else weekdayy = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7; 
    //0 nedele, po 1, ut 2, str 3, ct 4, pa 5, so 6
    switch (weekdayy){
    case 1: return 6; break;  //pondeli -> +6 a je nedele
    case 2: return 5; break;
    case 3: return 4; break;
    case 4: return 3; break;
    case 5: return 2; break;
    case 6: return 1; break;
    default: return 0; break;} //nedele
    return 0;
}

int validateDate(int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, int* sundays, int* leap_count_year1, int* leap_count_year2){
    //ret 1 (true), if valid
    int days_in_m1 = daysInMonth(m1, y1);
    int days_in_m2 = daysInMonth(m2, y2); 
    if (y1 < 1600 || d1 < 1 || d1 > days_in_m1 || days_in_m1 == 0 
                  || d2 < 1 || d2 > days_in_m2 || days_in_m2 == 0
                  || y2 < y1 || h1 < 0 || h1 > 23 
                             || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 
                                                  || i2 < 0 || i2 > 59)
        return 0; //neni valid
   
    int convertedM1 = convertMonthToDay(m1, y1);
    int convertedM2 = convertMonthToDay(m2, y2);

    //leapYears[ARRAY_SIZE], //leap_count_year je jakoze +kolik dni pricist, kolik roku až do y1/y2 bylo prestupnych a kolik dni musim pricist
    for (int i = 1600; i < y1; i++){
        if (i >= ARRAY_SIZE) break;
        if (leapYears[i-1600] == 1) (*leap_count_year1)++; //-1600 cuz od toho roku se to pocita, jen do <y1 cuz <=y1 uz do toho pocitam v convertM1
    }
    *leap_count_year2 = *leap_count_year1; //muzu to zrychlit jednoduse i*=4, ale pozdeji

    for (int i = y1; i<y2; i++){ //y1 cuz uz y1-1 je checkle
        if (i >= ARRAY_SIZE) break;
        if (leapYears[i-1600] == 1) (*leap_count_year2)++;
    }
    
    long long int interval1 = ((long long int)y1*365 + convertedM1 + d1 + *leap_count_year1)*24*60 + (h1 * 60) + (i1); //v minutach
    long long int interval2 = ((long long int)y2*365 + convertedM2 + d2 + *leap_count_year2)*24*60 + (h2 * 60) + (i2); //v minutach
    if (interval1 > interval2) return 0; //druhy interval je pred zacatkem prvniho

    int oKolikDniJeNedele_1 = weekday(d1, m1, y1);
    int oKolikDniJeNedele_2 = weekday(d2, m2, y2);

    int count = ( (y2*365 + convertedM2 + *leap_count_year2 + d2+oKolikDniJeNedele_2)-(y1*365 + *leap_count_year1 +convertedM1 + d1+oKolikDniJeNedele_1) ) / 7;
    *sundays = count;
    return 1;
}

int convertMonthToDay(int month, int year){ //vesme kolik dni uz ubehlo bez aktualnich dni v mesici, takze jen predesle mesice
    int x = 0;
    int feb = (isLeap(year)) ? 29:28;
    switch(month-1){ 
        case 1: x=31; break; //unor
        case 2: x = 31 + feb; break; //brezen
        case 3: x = 62 + feb; break; //duben
        case 4: x = 92 + feb; break; //kveten
        case 5: x = 123 + feb; break; //cerven
        case 6: x = 153 + feb; break; //cervenec
        case 7: x = 184 + feb; break; //srpen
        case 8: x = 215 + feb; break; //zari
        case 9: x = 245 + feb; break; //rijen
        case 10: x = 276 + feb; break; //listopad
        case 11: x = 306 + feb; break; //prosinec, ale bez nej, musim k tomu pricist aktualni dny prosince
        default: break;} //mesic je leden, takze jej nepricitame, cuz jen dny
    return x;
}

int daysInMonth(int month, int year){ //and checks if given month is valid
    //ret number of days in given month, 0 = incorrect month, so i don't need to check if m > 12 || m <1 - ret 0
    switch (month){
    case 1: case 3:  case 5: case 7: case 8: case 10: case 12: return 31; break;
    case 4: case 6: case 9: case 11: return 30; break;
    case 2: if (isLeap(year)==1) return 29; else return 28; break; 
    default: return 0; break;}
}

int isLeap(int year){

    if ( year % 4 != 0 ) return 0;
    if ( year % 100 != 0 ) return 1;
    if ( year % 400 != 0 ) return 0;
    if ( year % 4000 == 0) return 0;
    return 1;
}