#include <stdio.h>
#include <math.h>

unsigned short int PrimeNumber(unsigned long long int n){
    unsigned long long int a, i;

    a = sqrt(n);
    if (a*a == n || a % 2 == 0)
        return 0;

    for(i = 3; i < a; i+=2){
        if (n % i == 0)
            return 0;
    }
    return 1;

}

int main() {
    unsigned long long int n;
    scanf("%llu", &n);

    if (n < 2)
        printf("!ERROR!\n");
    else if (PrimeNumber(n))
        printf("A prime number!\n");
    else
        printf("Not a prime number!\n");

    return 0;
}
