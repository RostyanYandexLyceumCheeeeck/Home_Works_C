#include <stdio.h>
double pow( double x, double y );

int x, y;


int main() {
    int z = -pow(2, 31);
    printf("z = %d\n", z);

    // ввод переменных
    printf("Enter a number x: ");
    scanf("%d", &x);
    printf("Enter a number y: ");
    scanf("%d", &y);

    // арифметические операторы
    printf("addition: %d\n", x + y);
    printf("subtraction x - y: %d\n", x - y);
    printf("subtraction y - x: %d\n", y - x);
    printf("multiplication: %d\n", x * y);
    if (y != 0){
        printf("division x/y: %d\n", x / y);
        printf("division(result float) x/y: %.6f\n", x / (y * 1.0));
        printf("remainder of division x%%y: %d\n", x % y);
    }
    else printf("На ноль делить нельзя :(");

    // операторы сравнения
    printf("x > y: %d\n", x > y);
    printf("x < y: %d\n", x < y);
    printf("x == y: %d\n", x == y);
    printf("x >= y: %d\n", x >= y);
    printf("x <= y: %d\n", x <= y);
    printf("x != y: %d\n", x == y);

    // логические операторы
    printf("x && y: %d\n", x && y);
    printf("y || x: %d\n", x || y);
    printf("!y: %d\n", !y);
    printf("!x: %d\n", !x);

    // побитовые операторы
    printf("x & y: %d\n", x & y);
    printf("y | x: %d\n", x | y);
    printf("x ^ y: %d\n", x ^ y);
    printf("~x: %d\n", ~x);
    printf("~y: %d\n", ~y);

    // сдвиги
    printf("x << 2: %d\n", x << 2);
    printf("x >> 2: %d\n", x >> 2);
    printf("y << 2: %d\n", y << 2);
    printf("y >> 2: %d\n", y >> 2);

    // переполнение
    printf("-(2^31) - 1000: %d\n", z - 1000);
    printf("(2^31) + 1000: %d\n", -z + 1000);

    // деление на 0
    // printf("division x/0: %.6f\n", x / 0);

    return 0;
}