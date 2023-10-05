#include <stdio.h>


int main() {
    unsigned short x;
    scanf("%hu", &x);

    if(x % 4)
        printf("The year is not a leap year!\n");
    else if (x % 100)
        printf("Leap year!\n");
    else if (x % 400 == 0)
        printf("Leap year!\n");
    else printf("The year is not a leap year!\n");

    return 0;
}