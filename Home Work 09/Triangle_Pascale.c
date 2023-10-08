#include <stdio.h>
#include <windows.h>

void nullCheck(void* ptr);
void printArr(int* arr, size_t len);
int** createTrianglePascale(size_t* n);
void fillTrianglePascale(int** arr, size_t n);
void printTrianglePascalle(int** arr, size_t n);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t n;

    int** arr = createTrianglePascale(&n);
    fillTrianglePascale(arr, n);

    printTrianglePascalle(arr, n);

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

int** createTrianglePascale(size_t* n){
    size_t m;
    printf("Введите размер:");
    scanf("%zu", &m);

    int** arr = malloc(m * sizeof(int*));
    for (size_t i = 1; i < m + 1; i++) {
        arr[i - 1] = (int*) malloc(i * sizeof(int));
        nullCheck(arr[i - 1]);
    }
    *n = m;
    return arr;
}

void fillTrianglePascale(int** arr, size_t n){
    for(size_t i = 0; i < n; i++)
        arr[i][0] = arr[i][i] = 1;

    for(size_t i = 2; i < n; i++)
        for(size_t j = 1; j <= i / 2; j++)
            arr[i][j] = arr[i][i - j] = arr[i - 1][j - 1] + arr[i - 1][j];
}

void printTrianglePascalle(int** arr, size_t n){
    for(size_t i = 0; i < n; i++)
        printArr(arr[i], i+1);
}