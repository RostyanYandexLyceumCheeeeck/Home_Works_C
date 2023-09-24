#include <stdio.h>
#include <math.h>

unsigned long long int CountDivisors(unsigned long long int n){
    unsigned long long int a, i, k = 2;

    a = sqrt(n);
    if (a*a == n)
        k++;
    for(i = 2; i < a; i++){
        if (n % i == 0)
            k += 2;
    }

    return k;
}

int main() {
    unsigned long long int n;
    scanf("%llu", &n);

    if (n > 0)
        printf("%llu \n", CountDivisors(n));
    else printf("!ERROR!\n");

    return 0;
}
