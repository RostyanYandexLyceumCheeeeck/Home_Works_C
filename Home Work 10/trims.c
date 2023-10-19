#include <stdio.h>
#include <string.h>
#include <windows.h>


void nullCheck(void* ptr);
char* scanStr();
char* trim(char* st);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    char* st = scanStr();
    printf("\nВы ввели строку:\n\"%s\"\n", st);
    char* st_trim = trim(st);
    printf("\nНовая строка без пробелов в начале и в конце:\n\"%s\"\n", st_trim);

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

char* trim(char* st){
    size_t i, len = strlen(st);
    char* result = (char*) malloc(len-- * sizeof(char));
    char* ptr = result;

    for (i = 0; i < len;){
        if (st[i] == ' ')
            i++;
        if (st[len] == ' ')
            len--;
        else if (st[i] != ' ')
            break;
    }
    result = (char*) realloc(result, (len - i + 2) * sizeof(char));

    while(i <= len)
        *ptr++ = st[i++];
    *ptr = '\0';

    return result;
}
