#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

void rotateArray (int array [], int arrayLen, int rotateBy){
  rotateBy = rotateBy % arrayLen;
  if (rotateBy == 0) return; //0, takze arr zustava stejny
  
  int rotate, flag = 1; //flag 1 = doprava, 0 = doleva
  if(rotateBy>0) {rotate = arrayLen-rotateBy; flag = 0;}
  else {rotate = arrayLen+rotateBy; flag = 1;}

  if (rotate < rotateBy) {
    rotateBy = rotate;
    if (flag == 0) rotateBy *= (-1);
  }
  
  
  if (rotateBy > 0 ) {
    for (int i = 0; i < rotateBy; i++){
      int temp = array[arrayLen-1]; 
      for (int j = arrayLen-1; j > 0; j--){
        array[j] = array[j-1];
      }
      array[0] = temp;
    }
  }else {
    rotateBy *= (-1);
    for (int i = 0; i < rotateBy; i++){
      int temp = array[0]; 
      for (int j = 0; j < arrayLen-1; j++){
        array[j] = array[j+1];
      }
      array[arrayLen-1] = temp;
    }
  }
}



#ifndef __PROGTEST__
int identicalArrays ( const int a[], const int b[], int cnt ){
  for(int i = 0; i < cnt; i++){
    if (a[i] != b[i]) return 0;
  }
  return 1;
}

void printArr(int array[], int n){
  for (int i = 0; i<n; i++){
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main (int argc, char * argv [])
{
  int in0 []  = { 1, 2, 3, 4, 5 };
  int out0 [] = { 5, 1, 2, 3, 4 };

  int in1 []  = { 1, 2, 3, 4, 5 };
  int out1 [] = { 2, 3, 4, 5, 1 };

  int in2 []  = { 1, 2, 3, 4, 5, 6 };
  int out2 [] = { 4, 5, 6, 1, 2, 3 };

  int in3 []  = { 1, 2, 3, 4, 5, 6, 7 };
  int out3 [] = { 3, 4, 5, 6, 7, 1, 2 };

  int in4 []  = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int out4 [] = { 2, 3, 4, 5, 6, 7, 8, 9, 1 };

  rotateArray ( in0, 5, 1 );
  assert ( identicalArrays ( in0, out0, 5 ) );
  printArr(in0, 5);
  
  rotateArray ( in1, 5, -1 );
  assert ( identicalArrays ( in1, out1, 5 ) );
  printArr(in1, 5);
  
  rotateArray ( in2, 6, -3 );
  assert ( identicalArrays ( in2, out2, 6 ) );
  printArr(in2, 6);
  
  rotateArray ( in3, 7, 12 );
  assert ( identicalArrays ( in3, out3, 7 ) );
  printArr(in3, 7);
  
  rotateArray ( in4, 9, -100 );
  assert ( identicalArrays ( in4, out4, 9 ) );
  printArr(in4, 9);

  return 0;
}
#endif /* __PROGTEST__ */

