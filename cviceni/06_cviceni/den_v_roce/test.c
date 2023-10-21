#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int isLeap(int year){
    if ( year % 4 != 0 ) return 0;
    if ( year % 100 != 0 ) return 1;
    if ( year % 400 != 0 ) return 0;
    if ( year % 4000 == 0) return 0;
    return 1;
}

int daysInMonth(int month, int year){
    switch (month){
    case 1: case 3:  case 5: case 7: case 8: case 10: case 12: return 31; break;
    case 4: case 6: case 9: case 11: return 30; break;
    case 2: if (isLeap(year)==1) return 29; else return 28; break; 
    default: return 0; break;}
}


int dateToIndex(int day, int month, int year, int *idx) {
    if (year < 2000) return 0;
    int days_in_month = daysInMonth(month, year);
    if ((days_in_month == 0) || (day < 1 || day > days_in_month)) return 0;
    if (!isLeap(year) && day == 29) return 0;

    int x = 0;
    int feb = (isLeap(year)) ? 29:28;
    switch(month-1){ 
        case 1: x=31; break; //unor
        case 2: x = 31 + feb; break; //brezen
        case 3: x = 2*31 + feb; break; //duben
        case 4: x = 2*31 + feb + 30; break; //kveten
        case 5: x = 3*31 + feb + 30; break; //cerven
        case 6: x = 3*31 + feb + 2*30; break; //cervenec
        case 7: x = 4*31 + feb + 2*30; break; //srpen
        case 8: x = 5*31 + feb + 2*30; break; //zari
        case 9: x = 5*31 + feb + 3*30; break; //rijen
        case 10: x = 6*31 + feb + 3*30; break; //listopad
        case 11: x = 6*31 + feb + 4*30; break; //prosinec
        default: break; //mesic je leden, takze jej nepricitame, cuz jen dny
    }
    *idx = day + x;

    return 1;
}


#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    return 0;
}
#endif /* __PROGTEST__ */

