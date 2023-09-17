#include <stdio.h>
#include <math.h>

unsigned short int PrimeNumber(unsigned long long int n){
    unsigned long long int a, i;
    unsigned short int flag = 1;

    a = sqrt(n);
    if (a*a == n)
        flag = 0;
    else {
        for(i = 2; i <= a; i++){
            if (n % i == 0){
                flag = 0;
                break;
            }
        }
    }
    return flag;

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
