#include <stdio.h>


int main() {
    unsigned long n, i = 0, j, count = 1;
    scanf("%lu", &n);

    while(i < n*(n+1)/2){
        for(j = 0; j < count; j++){
            printf("%d\t", i);
            i++;
        }
        printf("\n");
        count++;
    }

    return 0;
}
