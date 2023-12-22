#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define DEBUG_MODE 0

#define ARENA_SIZE 10485760 // 10MB
#define BLOCK_SIZE 2048 // 2KB

typedef struct {
    void* data;
    void** ptrs;
    size_t* lens;
} Arena;

int N;
Arena ALL_MEMORY;
void nullCheck(void* ptr);

void initArena(Arena* arena) {
    arena->data = (void*) malloc((N + 1) * ARENA_SIZE * sizeof(void));
    arena->ptrs = (void**) malloc((N + 1) * sizeof(void*));
    arena->lens = (size_t*) malloc((N + 1) * sizeof(size_t));
    nullCheck(arena->data);
    nullCheck(arena->ptrs);
    nullCheck(arena->lens);

    for (int i = 0; i < N; i++) {
        arena->lens[i] = 0;
        arena->ptrs[i] = NULL;
    }
}

void start() {
    srand(time(NULL));
    N = (64 + rand() % 193) / 8;

    initArena(&ALL_MEMORY);
}

void* myMalloc(size_t size) {
    if (size % 8)
        size += 8 - (size % 8);
    if (!size || size > BLOCK_SIZE)
        return NULL;

    size_t data_ind = size / 8 - 1;
    if (size > N * 8) {
        size = BLOCK_SIZE;
        data_ind = N;
    }

    if (ALL_MEMORY.ptrs[data_ind] == NULL) {
        if (ALL_MEMORY.lens[data_ind] != ARENA_SIZE / size)
            return &ALL_MEMORY.data[data_ind * ARENA_SIZE + size * ALL_MEMORY.lens[data_ind]++];
        else
            return NULL;
    }
    else {
        void* res = ALL_MEMORY.ptrs[data_ind];
//        printf("res = %p\nptr = %p\n", res, *((void***) ALL_MEMORY.ptrs[data_ind]));
        ALL_MEMORY.ptrs[data_ind] = *((void***) ALL_MEMORY.ptrs[data_ind]);
        return res;
    }
}

void myFree(void* ptr) {
    size_t data_ind = (ptr - ALL_MEMORY.data) / ARENA_SIZE;
    if (ptr != NULL)
        *((void**) ptr) = ALL_MEMORY.ptrs[data_ind];

    ALL_MEMORY.ptrs[data_ind] = ptr;
//    printf("aaa = %p\nbbb = %p\n", *((void**) ptr), ALL_MEMORY.ptrs[data_ind]);
}

void* myRealloc(void* ptr, size_t size) {
    if (ptr == NULL)
        return NULL;
    void* res = myMalloc(size);
    if (res == NULL)
        return NULL;

    memcpy(res, ptr, (ptr - ALL_MEMORY.data) / ARENA_SIZE);
    myFree(ptr);
    return res;
}

#define DYN_ARR(T)                                                                                 \
    typedef struct {                                                                               \
        T* data;                                                                                   \
        size_t len;                                                                                \
        size_t cap;                                                                                \
    } MyArr_##T;                                                                                   \
                                                                                                   \
    void initEmptyMyArr_##T(MyArr_##T* arr) {                                                      \
        arr->len = 0;                                                                              \
        arr->cap = 1;                                                                              \
        arr->data = (T*) myMalloc(sizeof(T));                                                      \
        nullCheck(arr->data);                                                                      \
    }                                                                                              \
                                                                                                   \
    void addElemToMyArr_##T(MyArr_##T* arr, T elem) {                                              \
        arr->data[arr->len] = elem;                                                                \
        if (++arr->len == arr->cap) {                                                              \
            arr->cap *= 2;                                                                         \
            arr->data = (T*) myRealloc(arr->data, arr->cap * sizeof(T));                           \
            nullCheck(arr->data);                                                                  \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    void freeMyArr_##T(MyArr_##T* arr) {                                                           \
        myFree(arr->data);                                                                         \
    }

DYN_ARR(size_t)
size_t popMyArr_size_t(MyArr_size_t* arr);

DYN_ARR(char)
MyArr_char generateNewMyArr_char(char* st);
void addElemToNullTerminatedMyArr_char(MyArr_char* arr, char elem);

DYN_ARR(MyArr_char)
void freeFullMyArr_MyArr_char(MyArr_MyArr_char* arr);

void myMain(MyArr_MyArr_char* result, char* file_inp);

unsigned short handler(MyArr_MyArr_char* arr, size_t start, size_t finish);
unsigned short handlerBracket(MyArr_MyArr_char* arr, size_t start, size_t finish);
unsigned short handlerCalculation(MyArr_MyArr_char* arr, size_t start, size_t finish, char c);

void joinMyStr(MyArr_char* original, MyArr_char* copy);
unsigned short myStrIsWord(MyArr_char* st);
unsigned short myStrIsNumber(MyArr_char* st);
unsigned short myStrIsPalindrome(MyArr_char* st);

unsigned short charIsLetter(char c);
unsigned short charIsNumeric(char c);

int myAtoi(MyArr_char* st);

MyArr_char myItoa(int n);

#if DEBUG_MODE
void myprint(MyArr_MyArr_char* arr) {
    for (size_t j = 0; j < arr->len; j++)
        if (arr->data[j].len)
            printf("%s", arr->data[j].data);
}
#endif

int main() {
    start();
    MyArr_MyArr_char array;
    initEmptyMyArr_MyArr_char(&array);
    myMain(&array, "mte.txt");

    FILE* fileout = fopen("mout.txt", "w");
    nullCheck(fileout);
    for (size_t i = 0; i < array.len; i++) {
        fputs(array.data[i].data, fileout);
    }
    fclose(fileout);

    freeFullMyArr_MyArr_char(&array);
    return 0;
}

void myMain(MyArr_MyArr_char* result, char* file_inp) {

    FILE* filein = fopen(file_inp, "r");
    nullCheck(filein);

    MyArr_char st; // slova
    initEmptyMyArr_char(&st);
    MyArr_char prep; // prepinaniya
    initEmptyMyArr_char(&prep);
    MyArr_MyArr_char array;
    initEmptyMyArr_MyArr_char(&array);

    int c;
    size_t count_n = 0;  // кол-во \n подряд идущих
    size_t count_sp = 0; // кол-во space подряд идущих

    while (TRUE) {
        c = fgetc(filein);
        if (c == EOF || (!charIsLetter(c) && !charIsNumeric(c))) {
            if (st.len) {
                if (myStrIsPalindrome(&st)) {
                    addElemToMyArr_MyArr_char(&array, generateNewMyArr_char("PALINDROM"));
                    freeMyArr_char(&st);
                } else {
                    addElemToMyArr_MyArr_char(&array, st);
                }
                initEmptyMyArr_char(&st);
            }
            if (c == EOF)
                break;

            if (c == '\n' && count_n++ < 2) {
                count_sp = 0;
                addElemToNullTerminatedMyArr_char(&prep, c);
            } else if (c == ' ' && !count_sp++ && !count_n) {
                count_n = 0;
                addElemToNullTerminatedMyArr_char(&prep, c);
            } else if (c != ' ' && c != '\n') {
                count_n = count_sp = 0;
                addElemToNullTerminatedMyArr_char(&prep, c);
            }

            if (prep.len) {
                addElemToMyArr_MyArr_char(&array, prep);
                initEmptyMyArr_char(&prep);
            }
            continue;
        }
        count_n = count_sp = 0;
        addElemToNullTerminatedMyArr_char(&st, c);
    }
    fclose(filein);

    freeMyArr_char(&st);
    freeMyArr_char(&prep);

    if (!array.len) {
        freeFullMyArr_MyArr_char(&array);
        return;
    }

#if DEBUG_MODE
    int xod = 0;
    printf("STEP %d\n", xod++);
    printf("\n-----------------------------------------------\n");
    myprint(&array);
#endif
    while (handler(&array, 0, array.len)) {
#if DEBUG_MODE
        printf("STEP %d\n", xod++);
        printf("\n-----------------------------------------------\n");
        myprint(&array);
#endif
        unsigned short early_str = FALSE;
        size_t ind_early_str = 0;

        for (size_t i = 0; i < array.len; i++) {
            MyArr_char* elem = &array.data[i];
            if (!elem->len)
                continue;
            if (!myStrIsWord(elem)) {
                early_str = FALSE;
                continue;
            }
            if (early_str) {
                joinMyStr(&array.data[ind_early_str], elem);
                elem->len = 0;
                continue;
            }
            early_str = TRUE;
            ind_early_str = i;
        }
#if DEBUG_MODE
        printf("\n-----------------------------------------------\n");
        myprint(&array);
        printf("\n===============================================\n");
#endif
    }

    for (size_t i = 0; i < array.len; i++) {
        MyArr_char* elem = &array.data[i];
        if (elem->len && !strchr(" \n", elem->data[0]))
            break;
        elem->len = 0;
    }

    for (size_t i = 0; i < array.len; i++) {
        if (array.data[i].len)
            addElemToMyArr_MyArr_char(result, array.data[i]);
        else
            freeMyArr_char(&array.data[i]);
    }
    freeMyArr_MyArr_char(&array);
}

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("Нехватает динамической памяти для создания массива!!!\n");
        exit(1);
    }
}

void addElemToNullTerminatedMyArr_char(MyArr_char* arr, char elem) {
    addElemToMyArr_char(arr, elem);
    addElemToMyArr_char(arr, '\0');
    arr->len--;
}

void freeFullMyArr_MyArr_char(MyArr_MyArr_char* arr) {
    for (size_t i = 0; i < arr->len; i++)
        freeMyArr_char(&arr->data[i]);
    freeMyArr_MyArr_char(arr);
}

unsigned short handler(MyArr_MyArr_char* arr, size_t start, size_t finish) {
    if (start >= finish || finish > arr->len)
        return FALSE;

    MyArr_size_t mas;
    initEmptyMyArr_size_t(&mas);
    size_t number_ind = 0;
    size_t count_n = 0;  // кол-во \n подряд идущих
    size_t count_sp = 0; // кол-во space подряд идущих
    unsigned short flag = FALSE, ind_flag_number = 0;

    for (; start < finish; start++) {
        MyArr_char* elem = &arr->data[start];
        if (!elem->len)
            continue;
        char c = elem->data[0];
        if (elem->len == 1) {
            if (c == '\n' || c == ' ') {
                if (c == '\n' && ++count_n > 2)
                    elem->len = 0;
                else if (c == ' ' && (count_n || count_sp++))
                    elem->len = 0;
                continue;
            }
            count_sp = count_n = 0;
            if (strchr("+-*/", c) && ind_flag_number) {
                while (++start < finish)
                    if (arr->data[start].len && !strchr(" \n", arr->data[start].data[0]))
                        break;

                if (start >= finish)
                    break;
                if (myStrIsNumber(&arr->data[start])) {
                    if (handlerCalculation(arr, number_ind, start, c))
                        flag = TRUE;
                }
                ind_flag_number = 0;
                count_sp = count_n = 0;
                start--;
                continue;
            }

            if (mas.len && c == ')') {
                if (handlerBracket(arr, popMyArr_size_t(&mas), start))
                    flag = TRUE;
            }
            if (c == '(')
                addElemToMyArr_size_t(&mas, start);
        }

        ind_flag_number = 0;
        count_sp = count_n = 0;
        if (myStrIsNumber(elem)) {
            number_ind = start;
            ind_flag_number = 1;
        } else if (myStrIsPalindrome(elem)) {
            freeMyArr_char(elem);
            arr->data[start] = generateNewMyArr_char("PALINDROM");
        }
    }

    freeMyArr_size_t(&mas);
    return flag;
}

unsigned short handlerBracket(MyArr_MyArr_char* arr, size_t start, size_t finish) {
    unsigned short flag = handler(arr, start + 1, finish);
    size_t i = start + 1, end = finish - 1, words = 0, no_seps = 0;

    for (; i <= end; i++) {
        MyArr_char* el = &arr->data[i];
        if (!el->len)
            continue;
        if (myStrIsWord(el))
            words++;
        else if (!strchr(" \n", el->data[0]))
            no_seps++;
        if (words >= 2)
            break;
    }
    if (words == 1 && !no_seps) {
        arr->data[start].len = 0;
        arr->data[finish].len = 0;
        flag = TRUE;
    }
    return flag;
}

unsigned short handlerCalculation(MyArr_MyArr_char* arr, size_t start, size_t finish, char c) {
    if (!arr->data[start].len || !arr->data[finish].len)
        return FALSE;
    if (arr->data[start].len > 9 || arr->data[finish].len > 9)
        return FALSE;
#if DEBUG_MODE
    printf("Calc activate!!!\ns = %s\nf = %s\n", arr->data[start].data, arr->data[finish].data);
#endif
    int left_number = myAtoi(&arr->data[start]);
    int right_number = myAtoi(&arr->data[finish]);
    int res = 0;
    unsigned short flag = FALSE;

    if (c == '+') {
        res = left_number + right_number;
    } else if (c == '-') {
        res = left_number - right_number;
    } else if (c == '*') {
        res = left_number * right_number;
    } else if (c == '/') {
        if (!right_number)
            flag = TRUE;
        else
            res = left_number / right_number;
    }
    for (; start <= finish; start++)
        arr->data[start].len = 0;

    freeMyArr_char(&arr->data[finish]);

    if (flag) {
        arr->data[finish] = generateNewMyArr_char("ERROR");
    } else {
        arr->data[finish] = myItoa(res);
    }
    return TRUE;
}

size_t popMyArr_size_t(MyArr_size_t* arr) {
    return arr->data[--arr->len];
}

MyArr_char generateNewMyArr_char(char* st) {
    MyArr_char res;
    initEmptyMyArr_char(&res);
    for (size_t i = 0; i < strlen(st); i++)
        addElemToNullTerminatedMyArr_char(&res, st[i]);
    return res;
}

void joinMyStr(MyArr_char* original, MyArr_char* copy) {
    for (size_t i = 0; i < copy->len; i++)
        addElemToNullTerminatedMyArr_char(original, copy->data[i]);
}

unsigned short myStrIsWord(MyArr_char* st) {
    if (!st->len)
        return FALSE;
    for (size_t i = 0; i < st->len; i++)
        if (!charIsLetter(st->data[i]) && !charIsNumeric(st->data[i]))
            return FALSE;
    return TRUE;
}

unsigned short myStrIsNumber(MyArr_char* st) {
#if DEBUG_MODE
    printf("MyStrIsNumber activate!!!%zu\n", st->len);
    if (st->len)
        printf("st = %s\n", st->data);
#endif
    if (!st->len)
        return FALSE;
    for (size_t i = 0; i < st->len; i++)
        if (!charIsNumeric(st->data[i]))
            return FALSE;
    return TRUE;
}

unsigned short myStrIsPalindrome(MyArr_char* st) {
    if (!st->len)
        return FALSE;
    for (size_t i = 0; i <= st->len / 2; i++) {
        unsigned short left_flag = charIsLetter(st->data[i]);
        unsigned short right_flag = charIsLetter(st->data[st->len - i - 1]);
        if (!left_flag || !right_flag || st->data[i] != st->data[st->len - i - 1])
            return FALSE;
    }
    return TRUE;
}

unsigned short charIsLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

unsigned short charIsNumeric(char c) {
    return (c >= '0' && c <= '9');
}

int myAtoi(MyArr_char* st) {
    size_t finish = 0, i = st->len - 1;
    int res = 0, sign = 1, base = 1;

    if (st->data[0] == '-')
        sign = -1;
    if (strchr("-+", *st->data))
        finish = 1;

    do {
        res += (int) (st->data[i] - '0') * base;
        base *= 10;
    } while (i && --i >= finish);
    return sign * res;
}

MyArr_char myItoa(int n) {
    MyArr_char res;
    initEmptyMyArr_char(&res);
    int sign = 1;
    if (n < 0)
        sign = -1;

    do {
        addElemToNullTerminatedMyArr_char(&res, (char) (sign * (n % 10) + '0'));
        n /= 10;
    } while (n);
    if (sign == -1)
        addElemToNullTerminatedMyArr_char(&res, '-');

    for (size_t i = 0; i < res.len / 2; i++) {
        char swap = res.data[i];
        res.data[i] = res.data[res.len - i - 1];
        res.data[res.len - i - 1] = swap;
    }
    return res;
}
