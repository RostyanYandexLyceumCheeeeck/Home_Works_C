#include <stdio.h>
#include <windows.h>


unsigned int N;
unsigned short int PlayingGame;

struct PacMan
{
    unsigned long long int score;
    unsigned int x_coord, y_coord;
};

void paint(struct PacMan *obj);
void move(struct PacMan *obj, unsigned short int);
void start(struct PacMan *obj);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    struct PacMan game;
    unsigned short int step;

    printf("Введите размер игрового поля:");
    scanf("%u", &N);
    start(&game);

    while (PlayingGame){
        // system("cls");
        printf("Score: %llu\n", game.score);
        paint(&game);
        printf("Ваш ход:");
        scanf("%hu", &step);
        move(&game, step);
    }
    printf("Score: %llu\n", game.score);
    printf("Game Over!");


    return 0;
}

void start(struct PacMan *obj) {
    obj->x_coord = obj->y_coord = obj->score = 0;
    PlayingGame = 1;
}

void move(struct PacMan *obj, unsigned short int command) {
    // unsigned int* x = &obj->x_coord;
    // unsigned int* y = &obj->y_coord;

    obj->score++;
    if (command == 4) {
        if (obj->x_coord != 0)
            obj->x_coord--;
    }
    else if (command == 6) {
        if (obj->x_coord != N - 1)
            obj->x_coord++;
    }
    else if (command == 5) {
        if (obj->y_coord != N - 1)
            obj->y_coord++;
    }
    else if (command == 8) {
        if (obj->y_coord != 0)
            obj->y_coord--;
    }
    else obj->score--;

    if (obj->x_coord == N - 1 && obj->y_coord == N - 1)
        PlayingGame = 0;
}

void paint(struct PacMan *obj) {
    unsigned long int i, j;

    for(i = 0; i <= 2 * N; i++){
        for(j = 0; j <= 2 * N; j++){

            if (2 * obj->y_coord + 1 == i && 2 * obj->x_coord + 1 == j) {
                printf("  @  ");
                continue;
            }
            if (i == 2 * N - 1 && j == 2 * N - 1){
                printf("  #  ");
                continue;
            }

            if (i % 2) {
                if (j % 2)
                    printf("     ");
                else printf("|");
            }
            else if (j % 2)
                printf(" --- ");
            else printf("+");
        }
        printf("\n");
    }
}