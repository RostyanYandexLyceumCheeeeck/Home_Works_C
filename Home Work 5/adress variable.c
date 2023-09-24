#include <stdio.h>
#include <windows.h>


void adress_one();
void adress_two();


int main() {
    adress_one();
    adress_two();
    return 0;
}

void adress_one(){
    int a;
    printf("adress: %p\n", &a);
}

void adress_two(){
    adress_one();
}

