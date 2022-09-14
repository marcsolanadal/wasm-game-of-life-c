#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <ncurses.h>

#define WORLD_SIZE 80

void delay(int milliseconds) {
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int getNeightborCount(const int (*world)[WORLD_SIZE], int x, int y) {
    int count = 0;

    for(int j = (x - 1); j <= (x + 1); j++) {
        for(int k = (y - 1); k <= (y + 1); k++) {
            if ((j >= 0 && j < WORLD_SIZE) && (k >= 0 && k < WORLD_SIZE)) { // inside world?
                if (j != x || k != y) { // exculde current point
                    count += world[j][k];
                }
            } 
        }
    }

    return count;
}

void generateWorld(int world[WORLD_SIZE][WORLD_SIZE]) {
    time_t seed;
    srand((unsigned) time(&seed));

    for(int x = 0; x < WORLD_SIZE; x++) {
        for(int y = 0; y < WORLD_SIZE; y++) {
            world[x][y] = rand() % 2;
        }
    }
}

void printWorldState(const int (*world)[WORLD_SIZE]) {
    for(int x = 0; x < WORLD_SIZE; x++) {
        for(int y = 0; y < WORLD_SIZE; y++) {
            if (world[x][y] == 1) {
                mvprintw(x, y, "o");
            } else {
                mvprintw(x, y, " ");
            }
        }
    }
}

void tick(int (*world)[WORLD_SIZE]) {
    int nextWorld[WORLD_SIZE][WORLD_SIZE];

    for(int x = 0; x < WORLD_SIZE; x++) {
        for(int y = 0; y < WORLD_SIZE; y++) {
            int n = getNeightborCount(world, x, y);

            if (world[x][y] == 1) {
                if (n < 2 || n > 3) {
                    nextWorld[x][y] = 0;
                } else {
                    nextWorld[x][y] = 1;
                }
            } else {
                if (n == 3) {
                    nextWorld[x][y] = 1;
                } else {
                    nextWorld[x][y] = 0;
                }
            }
        }
    }

    for(int i = 0; i < WORLD_SIZE; i++) {
       memcpy(&world[i], &nextWorld[i], WORLD_SIZE * sizeof(int));
    }
}

int main(void) {
    initscr();
    noecho();
    curs_set(FALSE);
    setlocale(LC_CTYPE, "");

    int world[WORLD_SIZE][WORLD_SIZE];
    
    generateWorld(world);

    while(1) {
        clear();

        tick(world);
        printWorldState(world);

        refresh();
        delay(150);
    }
    
    endwin();

    return EXIT_SUCCESS;
}
