#include<stdio.h>
#include<stdlib.h>

#define INIT_MULTIPLY_FACTOR 2
#define INIT_ARR_SIZE 10

typedef struct interval{
    int from, to;
    char leftBracket, rightBracket;
} interval_t;

typedef struct points_arr{
    size_t size;
    size_t capacity;
    int *data;
} points_arr_t;

void countStudentsInInterval(int from, int to, points_arr_t *arr);
void determineInterval(interval_t *interval, points_arr_t *arr);
int isValidInterval(interval_t *interval);
int compare_nums(const void* num1, const void* num2);
points_arr_t arr_init();
void array_push_back(points_arr_t *arr, int num);
void array_destroy(points_arr_t *arr);
int lower_bound(int from, int arr[], int size);
int upper_bound(int to, int arr[], int size);

int lower_bound(int from, int arr[], int size){
    int low = 0, mid, high = size;
    while(low < high){
        mid = low + (high-low) / 2;
        if (from <= arr[mid]) high = mid; //levej kus pole
        else low = mid + 1; //pravej kus pole
    }
    if (low < size && arr[low] < from) low++;
    return low;
}

int upper_bound(int to, int arr[], int size){
    int low = 0, mid, high = size;
    while (low < high){
        mid = low + (high-low) / 2;
        if (to < arr[mid]) high = mid; //levej kus pole
        else low = mid +1;  //pravej kus pole
    }
    if (low < size && arr[low] <= to) low++;
    return low;
}

int isValidInterval(interval_t *interval){
    if ((interval->leftBracket != '(' && interval->leftBracket != '<') || (interval->rightBracket != ')' && interval->rightBracket != '>')) return 0;    
    return 1;
}

void determineInterval(interval_t *interval, points_arr_t *arr){
    switch (interval->leftBracket){
    case '(':   //otevreny zlevy
        if (interval->rightBracket == ')') countStudentsInInterval(interval->from+1, interval->to-1, arr);    //otevreny zleva i zprava     
        else countStudentsInInterval(interval->from+1, interval->to, arr);                        //otevreny zleva, uzavreny z prava
        break;
    case '<':       //uzavreny zleva
        if (interval->rightBracket == '>') countStudentsInInterval(interval->from, interval->to, arr); //uzavreny zleva i zprava
        else countStudentsInInterval(interval->from, interval->to-1, arr);                 //uzavreny zleva, otevreny zprava
        break;
    default: break;
    }
}

void countStudentsInInterval(int from, int to, points_arr_t *arr){
    int studentCounter = 0;
    int lowerBound = lower_bound(from, arr->data, arr->size);
    int upperBound = upper_bound(to, arr->data, arr->size);
    studentCounter = upperBound - lowerBound;
    if (studentCounter < 0) studentCounter = 0;
    printf(" -> %d\n", studentCounter);
}

int main(){
    interval_t interval;
    points_arr_t points_arr = arr_init();
    int num;
    char left_br, comma_right;

    printf("Pocty bodu:\n"); //{ 1, 7, 22, 4, 7, 5, 11, 9, 1 }  
    if (scanf(" %c ", &left_br) != 1 || left_br != '{'){ printf("Nespravny vstup.\n"); return 1; }
    while(1){
        int res = scanf(" %d %c", &num, &comma_right);
        if (res != 2 || (comma_right != ',' && comma_right != '}') || num > 1000000000 || num < 0){ printf("Nespravny vstup.\n"); return 1; }
        array_push_back(&points_arr, num);
        if (comma_right == '}') break; //konec vstupu body
    }
    qsort(points_arr.data, points_arr.size, sizeof(int), compare_nums); //sort, aby se pak jednoduse odecitaly indexy pole -> vysledek

    printf("Intervaly:\n");
    while(1){ //nacitani intervalu
        int returnValue = scanf(" %c %d ; %d %c", &interval.leftBracket, &interval.from, &interval.to, &interval.rightBracket);
        if (returnValue == EOF) break;
        else if ( returnValue != 4 || !isValidInterval(&interval)) { printf("Nespravny vstup.\n"); return 1; }
        determineInterval(&interval, &points_arr);
    }
    array_destroy(&points_arr);
    return 0;   
}

int compare_nums(const void* num1, const void* num2){ //cppreference
    int a = *(const int*)num1;
    int b = *(const int*)num2;
    return (a > b) - (a < b);
}

void array_destroy(points_arr_t *arr){
    free(arr->data);
    arr->data=NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void array_push_back(points_arr_t *arr, int num){
    if (arr->size >= arr->capacity){
        arr->capacity = INIT_MULTIPLY_FACTOR * arr->size;
        arr->data = (int*) realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size] = num;
    arr->size++;
}

points_arr_t arr_init(){
    points_arr_t arr;
    arr.size = 0;
    arr.capacity = INIT_ARR_SIZE;
    arr.data = (int*) malloc (arr.capacity * sizeof(int));
    return arr;
}