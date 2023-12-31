#include <stdio.h>
#include <windows.h>

void nullCheck(void* ptr);
void printArr(int* arr, size_t len);
int* scanArr(size_t* size);
int* concat(int* arr, int* brr, size_t alen, size_t blen);
void copyArr(int* arr, int* brr, size_t alen);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t n, m;
    int* arr = scanArr(&n);
    int* brr = scanArr(&m);
    int* crr = concat(arr, brr, n, m);
    printArr(crr, n + m);

    free(arr);
    free(brr);
    free(crr);
    return 0;
}

void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
}

void printArr(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int* scanArr(size_t* size){
    printf("Введите размерность массива:");
    scanf("%zu", &*size);

    int* arr = (int*) malloc(*size * sizeof(int));
    nullCheck(arr);

    printf("Введите %zu элементов массива:\n", *size);
    for(size_t i = 0; i < *size; i++)
        scanf("%d", &arr[i]);
    return arr;
}

int* concat(int* arr, int* brr, size_t alen, size_t blen){
    int* crr = (int*) malloc((alen + blen) * sizeof(int));
    nullCheck(crr);

    copyArr(arr, crr, alen);
    copyArr(brr, &crr[alen], blen);
    return crr;
}

void copyArr(int* arr, int* brr, size_t alen){
    for(size_t i = 0; i < alen; i++)
        brr[i] = arr[i];
}
