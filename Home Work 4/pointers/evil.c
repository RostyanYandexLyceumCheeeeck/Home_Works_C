#include <stdio.h>
#include <windows.h>


void evilScanf(int* p0, int *p1, int *p2);


int main(){
    SetConsoleOutputCP(CP_UTF8);
    int p0, p1, p2;

    printf("Введите 3 числа (значения р0 р1 р2):");
    scanf("%d %d %d", &p0, &p1, &p2);
    evilScanf(&p0, &p1, &p2);

    printf("Значения р0 р1 р2 после вызова функции: %d %d %d", p0, p1, p2);
    return 0;
}



void evilScanf(int* p0, int *p1, int *p2){
    int n0, n1, n2;
    printf("Введите 3 числа (значения n0 n1 n2):");
    scanf("%d %d %d", &n0, &n1, &n2);

    if (n0 > 0) {
        *p1 = n1;
        *p2 = n2;
    }
    else {
        *p2 = n0 * n1 * n2 * (*p1) * (*p2);
        *p1 = *p0;
    }
    *p0 = n0;
}