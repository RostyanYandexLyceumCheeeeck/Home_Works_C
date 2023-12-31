#include <stdio.h>
#include <string.h>
#include <windows.h>


void nullCheck(void* ptr);
char* scanStr();
unsigned short palindrom(char* st);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    char* st = scanStr();
    printf("\nВы ввели строку:\n\"%s\"\n", st);
    printf("Ваша строка является палиндромом(0 - нет, 1 - да): %u\n", palindrom(st));
    return 0;
}

void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
}

char* scanStr(){
    printf("Запущена функция scanStr(). Введите строку. Концом ввода является символ `\n");

    size_t len = 0, capacity = 32;
    char* st = (char*) malloc(capacity * sizeof(char));
    char* ptr = st;
    nullCheck(ptr);

    do {
        scanf("%c", &*ptr);
        if (++len == capacity) {
            capacity *= 2;
            st = (char*) realloc(st, capacity * sizeof(char));
            nullCheck(st);
        }
    }
    while (*ptr++ != '`');
    *--ptr = '\0';
    st = (char*) realloc(st, len * sizeof(char));

    return st;
}


unsigned short palindrom(char* st){
    char* ptr = st + strlen(st) - 1;

    while (st <= ptr) {
        if (*st == ' ') {
            st++;
            continue;
        }
        if (*ptr == ' ') {
            ptr--;
            continue;
        }

        if ((*st != *ptr))
            return 0;
        else {
            st++;
            ptr--;
        }
    }

    return 1;
}
