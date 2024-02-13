#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

#define OPERATE "wWaAsSdD"
#define MAP_SIZE 4
#define Swap(a, b) do{int temp = a; a = b; b = temp;} while(0);

int g_map[MAP_SIZE + 2][MAP_SIZE + 2] = {0};

int RandNumber(int);
void NewBlock(void);
void Initiate(void);
void PrintMap(void);
bool Check(void);
bool Push(int);
bool Merge(int);


int main() {
    srand(time(NULL));
    Initiate();
    PrintMap();

    int opr;
    while (true) {
        opr = getch();
        bool change = false;
        if (strchr(OPERATE, opr) != NULL) {
            change = Push(opr);
            change = Merge(opr) || change;
            change = Push(opr) || change;
        }

        system("cls");
        change ? NewBlock() : NULL;
        PrintMap();

        if (Check() == false) {
            printf("Game Over\n");
            system("pause");
            break;
        }
    }
    return 0;
}


int RandNumber(int max) {
    return (rand() / (RAND_MAX / max + 1)) + 1;
}

void NewBlock(void) {
    int y, x;
    do {
        y = RandNumber(MAP_SIZE), x = RandNumber(MAP_SIZE);
    } while (g_map[y][x] != 0);
    g_map[y][x] = RandNumber(10) == 10 ? 4 : 2;
}

void Initiate(void) {
    NewBlock();
    NewBlock();
}

void PrintMap(void) {
    printf("\n");
    for (int y = 1; y <= MAP_SIZE; ++y) {
        for (int x = 1; x <= MAP_SIZE; ++x) {
            printf("%5d", g_map[y][x]);
        }
        printf("\n\n");
    }
}

#define UP (flag == 'w' || flag == 'W')
#define DOWN (flag == 's' || flag == 'S')
#define LEFT (flag == 'a' || flag == 'A')

bool Push(int flag) {
    bool change = false;
    for (int x = 1; x <= MAP_SIZE; ++x) {
        for (int y = (UP || LEFT ? 1 : MAP_SIZE); (UP || LEFT ? (y < MAP_SIZE) : (y > 1)); UP || LEFT ? y++ : y--) {
            if (g_map[UP || DOWN ? y : x][UP || DOWN ? x : y] == 0) {
                int i = (UP || LEFT ? (y + 1) : (y - 1));
                while ((UP || LEFT ? (i <= MAP_SIZE) : (i > 0)) && g_map[UP || DOWN ? i : x][UP || DOWN ? x : i] == 0) UP || LEFT ? i++ : i--;
                if ((UP || LEFT ? (i <= MAP_SIZE) : (i > 0))) {
                    change = true;
                    Swap(g_map[UP || DOWN ? y : x][UP || DOWN ? x : y], g_map[UP || DOWN ? i : x][UP || DOWN ? x : i])
                }
            }
        }
    }
    return change;
}

bool Merge(int flag) {
    bool change = false;

    if (UP || DOWN) {
        for (int x = 1; x <= MAP_SIZE; ++x) {
            for (int y = (UP ? 1 : MAP_SIZE); (UP ? (y < MAP_SIZE) : (y > 0)); UP ? y++ : y--) {
                if (g_map[y][x] == g_map[UP ? (y + 1) : (y - 1)][x] && g_map[y][x] != 0) {
                    change = true;
                    g_map[y][x] *= 2;
                    g_map[UP ? (y + 1) : (y - 1)][x] = 0;
                }
            }
        }
    } else {
        for (int y = 1; y <= MAP_SIZE; ++y) {
            for (int x = (LEFT ? 1 : MAP_SIZE); (LEFT ? (x < MAP_SIZE) : (x > 0)); LEFT ? x++ : x--) {
                if (g_map[y][x] == g_map[y][LEFT ? (x + 1) : (x - 1)] && g_map[y][x] != 0) {
                    change = true;
                    g_map[y][x] *= 2;
                    g_map[y][LEFT ? (x + 1) : (x - 1)] = 0;
                }
            }
        }
    }

    return change;
}

bool Check(void) {
    for (int y = 1; y <= MAP_SIZE; ++y) {
        for (int x = 1; x <= MAP_SIZE; ++x) {
            if (g_map[y][x] == g_map[y - 1][x] || g_map[y][x] == g_map[y + 1][x] ||
                g_map[y][x] == g_map[y][x - 1] || g_map[y][x] == g_map[y][x + 1] ||
                g_map[y][x] == 0) {
                return true;
            }
        }
    }
    return false;
}