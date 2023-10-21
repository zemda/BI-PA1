#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#endif /* __PROGTEST__ */

long long avg3 ( long long a, long long b, long long c ){
  long long avg = 0;
  unsigned long long avgU = 0;
  if (a > 0 && b > 0 && c > 0) {avgU = (a+b+c) / 3; printf("avgU: %lld\n", avgU);return avgU;}
  else {avg = (a + b + c) / 3; return avg;}
  //idk jak to udelat
  
  return avg;
}

#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
  assert ( avg3 ( 1, 2, 3 ) == 2 );
  assert ( avg3 ( -100, 100, 30 ) == 10 );
  assert ( avg3 ( 1, 2, 2 ) == 1 );
  assert ( avg3 ( -1, -2, -2 ) == -1 );
  assert ( avg3 ( LLONG_MAX, LLONG_MAX, LLONG_MAX ) == LLONG_MAX );
  return 0;
}
#endif /* __PROGTEST__ */

