#include <stdio.h>
#include <string.h>
#include <windows.h>


void nullCheck(void* ptr);
//void my_realloc(char** masStr, char* st, size_t i, size_t* len);
char* scanStr();
unsigned short palindrom(char* st);
char* trim(char* st);
char** split(char* st, size_t* size);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t qwe = 0;
    char* st = scanStr();
    printf("%s\n", st);
    printf("%d\n", palindrom(st));
    trim(st);
    char** m = split(st, &qwe);
    printf("YEP!\n");

    typeof(st) asd = st;
    printf("%s", asd);
    for (size_t i = 0; i < qwe; i++)
        printf("%s\n", m[i]);
    return 0;
}

void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
}
//
//void my_realloc(char** masStr, char* st, size_t i, size_t* len){
//    if (i == *len){
//        *len *= 2;
//        if (masStr){
//            masStr = (char**) realloc(masStr, *len * sizeof(char*));
//            nullCheck(masStr);
//        }
//        else if (st){
//            printf("*\n");
//            st = (char*) realloc(st, *len * sizeof(char));
//            nullCheck(st);
//            printf("*\n");
//        }
//    }
//}

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

