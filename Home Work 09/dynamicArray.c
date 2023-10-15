#include <stdio.h>
#include <windows.h>


void nullCheck(void* ptr);
void* scanArr(size_t* len, size_t* capacity);
void printArr(int* arr, size_t len);


int main() {
    SetConsoleOutputCP(CP_UTF8);
    size_t n, m;

    //
    printf("Тестирование функций scanArr и printArr.\nВводите элементы массива(признак окончания ввода = 0):\n");
    int* arr = (int*) scanArr(&n, &m);
    printArr(arr, n);

    free(arr);
    return 0;
}

void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
}

void* scanArr(size_t* len, size_t* capacity){
    size_t left = 0, right = 1;
    int* brr = (int*) malloc(right * sizeof(int));
    nullCheck(brr);

    int elem = 1;
    while(elem){
        scanf("%d", &elem);
        brr[left] = elem;

        if (++left == elem) {
            right *= 2;
            brr = (int*) realloc(brr, right * sizeof(int));
            nullCheck(brr);
        }
    }

    *len = left;
    *capacity = right;
    return brr;
}
void printArr(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

