#include <stdio.h>


int main() {
    unsigned long n, i, j;
    scanf("%lu", &n);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++)
            printf("%lu\t", i*n + j);
        printf("\n");
    }

    return 0;
}
