#include <stdio.h>
#include <windows.h>



unsigned int Euclid_algorithm(unsigned a, unsigned b);


int main() {
    SetConsoleOutputCP(CP_UTF8);

    unsigned x, y;
    printf("Введите 1 число:");
    scanf("%u", &x);
    printf("Введите 2 число:");
    scanf("%u", &y);

    printf("\nНаибольший общий делитель чисел %u и %u = %u", x, y, Euclid_algorithm(x, y));
    return 0;
}

unsigned int Euclid_algorithm(unsigned a, unsigned b){
    while (a && b)
        if (a > b)
            a %= b;
        else b %= a;

    return a + b;
}
