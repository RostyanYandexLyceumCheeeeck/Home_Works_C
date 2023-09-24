#include <stdio.h>


int main() {
    unsigned long l, r, copy;
    unsigned int one, two;
    short i;

    scanf("%lu %lu", &l, &r);
    if (l > r){
        printf("!ERROR!\n");
        return 0;
    }

    if (r <= 100000 || l >= 1000000) return 0;
    if (l < 100000) l = 100000;
    if (r > 1000000) r = 1000000;

    while(l < r){
        copy = l;
        one = two = 0;

        for(i = 0; i < 6; i++){
            if (i < 3) two += copy % 10;
            else one += copy % 10;
            copy /= 10;
        }

        if (one == two)
            printf("%lu\t", l);
        l++;
    }
    printf("\n");

    return 0;
}
