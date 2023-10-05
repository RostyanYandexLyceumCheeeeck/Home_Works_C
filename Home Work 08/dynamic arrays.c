#include <stdio.h>
#include <windows.h>


void scanArr(int* arr, size_t len);
void printArr(int* arr, size_t len);
void revertArr(int* arr, size_t len);
int maxInArr(int* arr, size_t len);
void* finInArr(int* arr, size_t len, int x);
void extractDigits(int* arr, size_t len, int x);
int compareArrays(int* arr, int* brr, size_t alen, size_t blen);


int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t n, m;
    int x;

    //
    printf("Тестирование функций scanArr и printArr. Введите размер массива:");
    scanf("%zu", &n);
    int* arr = (int*) malloc(n * sizeof(int));
    printf("Введите массив длины %zu:\n", n);
    scanArr(arr, n);
    printArr(arr, n);

    //
    printf("\nТестирование функции revertArr:\n");
    revertArr(arr, n);
    printArr(arr, n);

    //
    printf("\nТестирование функции maxInArr. Максимальный элемент массива: %d\n\n", maxInArr(arr, n));

    //
    printf("Тестирование функции finInArr. Введите искомое число:");
    scanf("%d", &x);
    printf("Адрес(0 = NULL) числа %d в массиве = %p\n\n", x, finInArr(arr, n, x));

    //
    printf("Тестирование функции extractDigits. Введите число:");
    scanf("%d", &x);
    extractDigits(arr, n, x);
    printArr(arr, n);

    //
    printf("\nТестирование функции compareArrays. Введите размер массива:");
    scanf("%zu", &m);
    int* brr = (int*) malloc(m * sizeof(int));
    printf("Введите массив длины %zu:\n", m);
    scanArr(brr, m);
    printf("%d", compareArrays(arr, brr, n, m));

    free(arr);
    free(brr);
    return 0;
}

void scanArr(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
        scanf("%d", &arr[i]);
}
void printArr(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void revertArr(int* arr, size_t len){
    int c;
    for(size_t i = 0; i < len / 2; i++){
        c = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = c;
    }
}

int maxInArr(int* arr, size_t len){
    int max = arr[0];
    for(size_t i = 1; i < len; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void* finInArr(int* arr, size_t len, int x){
    for(size_t i = 0; i < len; i++){
        if (arr[i] == x)
            return &arr[i];
    }
    return NULL;
}

void extractDigits(int* arr, size_t len, int x){
    size_t count = 0;
    for(size_t i = 0; i < len && x > 0; i++){
        arr[i] = x % 10;
        x /= 10;
        count++;
    }
    revertArr(arr, count);
}

int compareArrays(int* arr, int* brr, size_t alen, size_t blen){
    for (size_t i = 0; i < min(alen, blen); i++){
        if (arr[i] < brr[i])
            return -1;
        if (arr[i] > brr[i])
            return 1;
    }
    if (alen < blen)
        return -1;
    else if (alen > blen)
        return 1;
    return 0;
}
