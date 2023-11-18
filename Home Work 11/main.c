#include <stdio.h>
#include <string.h>
#include <windows.h>


typedef struct {
    size_t len;
    size_t cap;
    char* data;
} MyString;

typedef struct {
    size_t len;
    size_t cap;
    MyString* array_str;
} MyArrayString;


void nullCheck(void* ptr);
void initEmptyStr(MyString* st);
void addElemToStr(MyString* st, char elem);
void freeMyStr(MyString* st);

void initEmptyArrayStr(MyArrayString* array);
void addElemToArrayStr(MyArrayString* array, MyString my_str);
void freeMyArrayStr(MyArrayString* array);
void splitMyStr(MyArrayString* array, MyString* st);

const MyString sep_space = {1, 2, " \0"};
const MyString sep_linefeed = {1, 2, "\n\0"};
//MyString sep_space;
//MyString sep_linefeed;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE* filein = fopen("inp.txt", "r");
//
//    initEmptyStr(&sep_space);
//    addElemToStr(&sep_space, ' ');
//    initEmptyStr(&sep_linefeed);
//    addElemToStr(&sep_linefeed, '\n');

    MyString st;
    initEmptyStr(&st);
    MyArrayString array;
    initEmptyArrayStr(&array);
    char c;
    int flag = 0; // кол-во \n подряд идущих
    while ((c = fgetc(filein)) != EOF) {
        if (array.len) break; // отладка
        putchar(c);
        if (c == '\n'){  // ломается здесь где-то
            if (!flag){
                // splitMyStr(&array, &st);
                addElemToArrayStr(&array, st);
                printf("YEP!\n");
                freeMyStr(&st);
                initEmptyStr(&st);
            }
            if (flag < 2)
                addElemToArrayStr(&array, sep_linefeed);
            flag++;
            continue;
        }
        flag = 0;
        addElemToStr(&st, c);
    }
    fclose(filein);
    // отладка (не доходит до сюда)
    printf("\nst:\n");
    for (size_t i = 0; i < st.len; i++) putchar(st.data[i]);
    printf("\narray:\n");
    for (size_t i = 0; i < array.len; i++)
        printf("%s", array.array_str[i].data);

    freeMyStr(&st);
    freeMyArrayStr(&array);
    return 0;
}

void nullCheck(void* ptr){
    if (ptr == NULL){
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(0);
    }
}

void initEmptyStr(MyString* st){
    st->cap = 1;
    st->len = 0;
    st->data = (char*) malloc(sizeof(char));
    nullCheck(st->data);
    st->data[0] = '\0';
}

void addElemToStr(MyString* st, char elem){
    st->data[st->len] = elem;
    if (++st->len == st->cap - 1){
        st->cap *= 2;
        st->data = (char*) realloc(st->data, st->cap * sizeof(char));
        nullCheck(st->data);
    }
    st->data[st->len] = '\0';
}

void freeMyStr(MyString* st){
    free(st->data);
}

void initEmptyArrayStr(MyArrayString* array){
    array->cap = 1;
    array->len = 0;
    array->array_str = (MyString*) malloc(sizeof(MyString));
    nullCheck(array->array_str);
}

void addElemToArrayStr(MyArrayString* array, MyString my_str){
    printf("do dobavlenia\n");
    array->array_str[array->len] = my_str;
    printf("posle\n");
    if (++array->len == array->cap){
        array->cap *= 2;
        printf("qwe\n");
        array->array_str = (MyString*) realloc(array->array_str, array->cap * sizeof(MyString));
        printf("asd\n");
        nullCheck(array->array_str);
    }
}

void freeMyArrayStr(MyArrayString* array){
    for (size_t i = 0; i < array->len; i++)
        freeMyStr(&array->array_str[i]);
    free(array);
}

void splitMyStr(MyArrayString* array, MyString* st){
    addElemToStr(st, ' ');
    MyString new_str;
    initEmptyStr(&new_str);
    char* data = st->data;
    int flag = 0; // кол-во скобочек

    for (size_t i = 0; i < st->len; i++){
        if (data[i] == '(')
            flag++;
        if (data[i] == ')')
            flag--;
        if (!flag && data[i] == ' '){
            if (new_str.len){
                addElemToArrayStr(array, new_str);
                addElemToArrayStr(array, sep_space);
                initEmptyStr(&new_str);
            }
            continue;
        }
        addElemToStr(&new_str, data[i]);
    }
}