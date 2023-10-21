#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <windows.h>


void nullCheck(void* ptr);
char* scanStr();
unsigned short int len_between_chars(char symbol, char start);
int s2i(char* st, unsigned short base, jmp_buf* code);
int max_value = 2147483647;
int min_value = -2147483648;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    jmp_buf env;
    int error = setjmp(env);
    if (error){
        printf("Ошибка в функции 's2i'! проверьте корректность данных:\n"
               "1) система счисления <= 16\n"
               "2) символы заглавные и лежат в диапазоне указанной системы счисления(в начале корректен -)\n"
               "3) Число должно лежать в диапазоне int в 10-тичной системе счисления\n");
        return error;
    }
    printf("%d\n", s2i("7FFFFFFF\0", 16, &env));
    printf("%d\n", s2i("-7FFFFFFF\0", 16, &env));
    printf("%d\n", s2i("-80000000\0", 16, &env));
    printf("%d\n", s2i("-00000000000000000000000000000000000080000000\0", 16, &env));
    printf("%d\n", s2i("80000000\0", 16, &env));

    return 0;
}

unsigned short int len_between_chars(char symbol, char start){
    if (symbol < start)
        return 100;
    return symbol - start;
}

int s2i(char* st, unsigned short base, jmp_buf* code){
    long long int result = 0, step_base = 1;
    unsigned short new, flag = (*st == '-');
    int sign = 1 - 2 * flag;
    size_t size = strlen(st);
    char symbol;

    for(size_t degree = 0; degree < size - flag; degree++) {
        symbol = st[size - degree - 1];
        new = min(len_between_chars(symbol, '0'), len_between_chars(symbol, 'A') + 10);

        result += step_base * sign * new;
        step_base *= base;

        if ((symbol > '9' && symbol < 'A') || base > 16 || new >= base ||
        result > max_value || result < min_value || (new && degree > 8)) {
            if  (*code)
                longjmp(*code, 1);
            printf("nekorrect_symbol = %d; base = %hu; new = %d; result = %lld; re>ma = %d;  re<mi = %d; n&d = %d; degree = %zu; symbol = %c\n", (symbol > '9' && symbol < 'A'), base, new, result, result > max_value, result < min_value, (new && degree > 8), degree, symbol);
            exit(2);
        }
    }
    return (int) result;
}