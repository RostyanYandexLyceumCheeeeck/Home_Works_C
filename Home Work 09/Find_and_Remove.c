#include <stdio.h>
#include <windows.h>

void nullCheck(void* ptr);
void printArr(int* arr, size_t len);
int* scanArr(size_t* size);
void copyArr(int* arr, int* brr, size_t alen);
void* findSubArr(int* arr, int* brr, size_t alen, size_t blen);
void removeSubArr(int* arr, int* brr, size_t* alen, size_t blen);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t n, m;
    int* arr = scanArr(&n);
    int* brr = scanArr(&m);

    printf("Тестирование findSubArr: %p\nТестирование removeSubArr:\n", findSubArr(arr, brr, n, m));
    removeSubArr(arr, brr, &n, m);
    printArr(arr, n);

    free(arr);
    free(brr);
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

void* findSubArr(int* arr, int* brr, size_t alen, size_t blen){
    size_t j = 0;

    for(size_t i = 0; i < alen; i++) {
        if (arr[i] != brr[j]) {
            j = 0;
            if (arr[i] == brr[j])
                j++;
        }
        else if (++j == blen)
            return &arr[i - j + 1];

        if (alen - i < blen - j)
            return NULL;
    }
    return NULL;
}

void removeSubArr(int* arr, int* brr, size_t* alen, size_t blen){
    int* ptr;
    while ((ptr = findSubArr(arr, brr, *alen, blen))){
        *alen -= blen;
        copyArr(ptr + blen, ptr, *alen - (ptr - arr));
    }
    realloc(arr, *alen);
}