#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/*
  Author: Daniel Žemla
          Banán#0026
*/

typedef struct string_arr{
  size_t size;
  size_t capacity;
  char *data;
} string_arr;

//Storing which words I should replace, their position in the original text and a key from the dictionary
typedef struct toBeReplaced{ 
  size_t keys_index_capacity;
  size_t keys_index_size;
  int* keys_index;
 
  size_t positions_capacity;
  size_t positions_size;
  long long int* positions;
} toBeReplaced;

string_arr initStringArr();
void pushStringArr(string_arr *arr, char x);
void destroyStringArr(string_arr *arr);

toBeReplaced initTbrArr();
void pushTbrArr(toBeReplaced *arr, int key_index, long long int position);
void destroyTbrArr(toBeReplaced *arr);

int countRowsInDict(const char* (*dict)[2]);
int isDictCorrect(const char * (*replace)[2], int length);
char* newSpeak(const char* text, const char* (*dict)[2]);
void sort(int *keys, long long int *positions, size_t size);
void countWordsToReplace(const char *text, const char *(*replace)[2], int dictLength, toBeReplaced *tbReplaced);
void replaceWordsInString(const char *text, toBeReplaced *tbReplaced, string_arr *string, const char *(*replace)[2]);

//Sorting the positions in toBeReplaced struct, couldn't use qsort from stdlib, since I needed to sort keys positions as well with it, so I do not replace the wrong words in a given position
void sort(int *keys, long long int *positions, size_t size) {

  for (size_t i = 1; i < size; i++) {
    int tmp = keys[i];
    int tmp2 = positions[i];
    int x = i - 1;
    
    while (x >= 0 && tmp2 < positions[x]) {
      keys[x+1] = keys[x];
      positions[x+1] = positions[x];
      x--;
    } 
    keys[x+1] = tmp;
    positions[x+1] = tmp2;
  }
}

//Checks if any word in a dictionary is not a prefix of another word.
int isDictCorrect(const char* (*dict)[2], int leng){
  for (int i = 0; i < leng-1; i++) {
    int wordLengI = strlen(dict[i][0]);
    int maxNumsToCompare = wordLengI;

    for (int k = i + 1; k < leng; k++){
      int wordLengK = strlen(dict[k][0]);
      if (wordLengK < wordLengI) maxNumsToCompare = wordLengK;
      else maxNumsToCompare = wordLengI;
      
      if (strncmp(dict[i][0], dict[k][0], maxNumsToCompare) == 0) return 0;
    }
  }
  return 1;
}

int countRowsInDict(const char* (*dict)[2]){
  int x = 0;
  while (dict[x][0] != NULL) x++;
  return x;
}

/*
  Key       -> dictionary index, which word have to be replaced
  Position  -> index, where the word starts in a given text

  Checks if there is a word in the given text to be replaced from the dictionary, if so, stores the position and key into "ToBeReplaced" structure -> at the end there's the exact number of how many replacements must be done
  -> Since it might find the word from the end of the text first, I have to sort it so I am replacing the words sequentially
*/
void countWordsToReplace(const char *text, const char *(*replace)[2], int dictLength, toBeReplaced *tbReplaced){
  for (int i = 0; i < dictLength; i++){ //i = keyindex
    int leng = strlen(replace[i][0]);
    char *key = (char*) malloc ((leng+1) * sizeof(char));
    const char* result = text;
    strcpy(key, replace[i][0]);
    while((result = strstr(result, key))){
      long long int position_in_text = result - text;
      pushTbrArr(tbReplaced, i, position_in_text);
      ++result;
    }
    free(key);
  }
}

//Function that does the main job - replacing words that were found with "countWordsToReplace" function.
void replaceWordsInString(const char *text, toBeReplaced *tbReplaced, string_arr *string, const char *(*replace)[2]){
  size_t textLength = strlen(text);
  int start_pos = 0, end_pos = 0, numOfOrigChars = textLength, printedOrigChars = 0;
  for (size_t i = 0; i < tbReplaced->keys_index_size; i++){
    int leng_inappropriate_word = strlen(replace[tbReplaced->keys_index[i]][0]);
    int leng_replacement_word = strlen(replace[tbReplaced->keys_index[i]][1]);
    char *replacement = (char*) malloc((leng_replacement_word+1) * sizeof(char));
    strcpy(replacement, replace[tbReplaced->keys_index[i]][1]);
    numOfOrigChars -= leng_inappropriate_word;
    
     
    //I need to check whether I still have to replace this word - that word still "exists" there (I did not replace it in a previous iteration), e.g son and prisoner are both inappropriate words, but first I have to replace the exact word - prisoner, not the sufix, which is stored/counted in toBeReplaced struct as well. 
    const char* res = strstr(text+start_pos, replace[tbReplaced->keys_index[i]][0]);
    if ( (res-text) != tbReplaced->positions[i]) {
      free(replacement);
      continue;
    }
    
    //Firstly I will append the appropriate part of the text into the new, politically correct text
    end_pos = tbReplaced->positions[i];
    for (int k = start_pos; k < end_pos; k++){
      char c = text[k];
      pushStringArr(string, c);
      printedOrigChars++;
    }
    start_pos = end_pos + leng_inappropriate_word;

    //And then I will replace the inappropriate word for their appropriate version
    for (int k = 0; k < leng_replacement_word; k++){
      char c = replacement[k];
      pushStringArr(string, c);
    }
    free(replacement);
  }

  //If the new corrected text is missing the end of the original inappropriate text, it will be fixed here and the new appropriate version is now complete.
  if (printedOrigChars < numOfOrigChars){
    for (size_t i = start_pos; i < textLength; i++){
      pushStringArr(string, text[i]);
    }
  }
  string->data[string->size] = '\0';
}

char* newSpeak ( const char * text, const char * (*replace)[2] ){
  int dictLength = countRowsInDict(replace);  
  if (!isDictCorrect(replace, dictLength)) return NULL;

  string_arr string = initStringArr();
  toBeReplaced tbReplaced = initTbrArr();
  
  countWordsToReplace(text, replace, dictLength, &tbReplaced);
  sort(tbReplaced.keys_index, tbReplaced.positions, tbReplaced.keys_index_size);
  replaceWordsInString(text, &tbReplaced, &string, replace);
  
  char* string2 = (char*) malloc((string.size+1) * sizeof(char));
  strcpy(string2, string.data);

  destroyTbrArr(&tbReplaced);
  destroyStringArr(&string);
  return string2;
}

#ifndef __PROGTEST__
int main (){
  char* res;
  const char* d1[][2] = {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };
  const char* d2[][2] = {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };
  const char* tbl [][2] = {
    { "son", "offspring with both X and Y chromosomes" },
    { "prisoner", "client of the correctional system" },
    { NULL, NULL }
  };

  res = newSpeak ( "son of a prisoner", tbl );
  assert ( ! strcmp ( res, "offspring with both X and Y chromosomes of a client of the correctional system" ) );
  free ( res );

  res = newSpeak ( "murderer is happy.", d1 );
  assert ( ! strcmp ( res, "termination specialist is happy." ) );
  free ( res );

  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );

  res = newSpeak ( "The student student student student student answered an student incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client client client client client answered an client alternative answer." ) );
  free ( res );

  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */


toBeReplaced initTbrArr(){
  toBeReplaced arr;
  arr.keys_index_capacity = 10;
  arr.keys_index_size = 0;
  arr.keys_index = (int*) malloc (arr.keys_index_capacity * sizeof(int));

  arr.positions_capacity = 10;
  arr.positions_size = 0;
  arr.positions = (long long int*) malloc (arr.positions_capacity * sizeof(long long int));
  return arr;
}

void pushTbrArr(toBeReplaced *arr, int key_index, long long int position){
  if (arr->keys_index_size >= arr->keys_index_capacity){
    arr->keys_index_capacity = arr->keys_index_size * 2;
    arr->keys_index = (int*) realloc(arr->keys_index, arr->keys_index_capacity * sizeof(int));
  }
  arr->keys_index[arr->keys_index_size] = key_index;

  if (arr->positions_size >= arr->positions_capacity){
    arr->positions_capacity = arr->positions_size * 2;
    arr->positions = (long long int*) realloc(arr->positions, arr->positions_capacity * sizeof(long long int));
  }
  arr->positions[arr->positions_size] = position;

  arr->keys_index_size++;
  arr->positions_size++;
}

void destroyTbrArr(toBeReplaced *arr){
  free(arr->keys_index);
  free(arr->positions);

  arr->keys_index_capacity = 0;
  arr->keys_index_size = 0;
  arr->positions_capacity = 0;
  arr->positions_size = 0;
}


string_arr initStringArr(){
  string_arr arr;
  arr.capacity = 10;
  arr.size = 0;
  arr.data = (char*) malloc (arr.capacity * sizeof(char));
  return arr;
}

void pushStringArr(string_arr *arr, char x){
  if (arr->size >= arr->capacity){
    arr->capacity = arr->size * 2;
    arr->data = (char*)realloc(arr->data, arr->capacity * sizeof(char));
  }
  arr->data[arr->size] = x;
  arr->size++;
}

void destroyStringArr(string_arr *arr){
  free(arr->data);
  arr->data = NULL;
  arr->capacity = 0;
  arr->size = 0;
}
