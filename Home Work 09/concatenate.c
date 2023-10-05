#include <stdio.h>
#include <windows.h>

void printArr(int* arr, size_t len);
void nullCheck(void* ptr);
int* scanArr(size_t* size);
int* concat(int* arr, int* brr, size_t alen, size_t blen);
void copyArr(int* arr, int* brr, size_t alen);
int* findSubArr(int* arr, int* brr, size_t alen, size_t blen);
void removeSubArr(int* arr, int* brr, size_t* alen, size_t blen);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t n, m, x;
    int* arr = scanArr(&n);
    int* brr = scanArr(&m);
    int* crr = concat(arr, brr, n, m);
    printArr(crr, n + m);

    x = n + m;
    printf("%d\n", *findSubArr(arr, brr, n, m));
    removeSubArr(crr, brr, &x, m);
    printArr(crr, x);

    free(arr);
    free(brr);
    free(crr);
    return 0;
}

void printArr(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
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

int* findSubArr(int* arr, int* brr, size_t alen, size_t blen){
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
    size_t i = 0, j;
    int* ptr = arr;

    while (i < *alen){
        ptr = findSubArr(ptr, brr, *alen, blen);
        if (ptr == NULL)
            break;

        i = ptr - arr;
        for(j = 0; j < min(*alen - i, blen); j++, i++)
            *(ptr + j) = arr[i + blen];
    }
    *alen = i;
    realloc(arr, i * sizeof(int));
}