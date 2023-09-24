#include <stdio.h>
#include <windows.h>
#include <stdlib.h>


void swap(int a, int b);
void point_swap(int* a, int* b);


int main() {
    SetConsoleOutputCP(CP_UTF8);

    int x, y;
    printf("Введите два числа:");
    scanf("%d %d", &x, &y);
    swap(x, y);
    printf("Работа функции swap(передали значения): %d %d", x, y);
    point_swap(&x, &y);
    printf("\nРабота функции point_swap(передали указатели): %d %d", x, y);

    return 0;
}

void swap(int a, int b){
    int c = a;
    a = b;
    b = c;
}

void point_swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}