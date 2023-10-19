#include <stdio.h>
#include <string.h>
#include <windows.h>


void nullCheck(void* ptr);
char* scanStr();
char** split(char* st, size_t* size);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t size = 0;
    char* st = scanStr();
    printf("\nВы ввели строку:\n\"%s\"\n", st);
    char** m = split(st, &size);
    printf("\nTesting function split!\n");
    printf("[");
    for (size_t i = 0; i < size; i++) {
        printf("\"%s\", ", m[i]);
        free(m[i]);
    }
    printf("]");
    free(m);
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

char** split(char* st, size_t* size){
    size_t i, j = 0, k = 0, countStr = 2, len = 8, finish = strlen(st);
    unsigned short flag =  0;
    char** masStr = (char**) malloc(countStr * sizeof(char*));
    char* newStr = (char*) malloc(len * sizeof(char));

    for(i = 0; i <= finish; i++){
        if (st[i] == ' ' || i == finish){
            if (flag){
                newStr[j++] = '\0';
                newStr = (char*) realloc(newStr, j * sizeof(char));
                masStr[k] = newStr;

                if(++k == countStr){
                    countStr *= 2;
                    masStr = (char**) realloc(masStr, countStr * sizeof(char*));
                    nullCheck(masStr);
                }
                newStr = (char*) malloc(len * sizeof(char));
                nullCheck(newStr);
            }
            j = flag = 0;
        }
        else {
            flag = 1;
            newStr[j] = st[i];
            if(++j == len) {
                len *= 2;
                newStr = (char*) realloc(newStr, len * sizeof(char));
                nullCheck(newStr);
            }
        }
    }
    free(newStr);

    *size = k;
    return masStr;
}

