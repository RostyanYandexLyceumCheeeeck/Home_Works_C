#include <stdio.h>


int main() {
    unsigned long n;
    scanf("%lu", &n);

    for(unsigned long i = 0; i < n; i++){
        if(i % 3 == 0 && i % 5 == 0)
            printf("fizz buzz\n");
        else if(i % 3 == 0)
            printf("fizz\n");
        else if(i % 5 == 0)
            printf("buzz\n");
    }

    return 0;
}
