#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE (uint32_t)40

#define CELL_ALIVE "\u2588\u2588"  // Full block
#define CELL_DEAD "  "

#define BORDER_H "\u2500"
#define BORDER_V "\u2502"
#define BORDER_TL "\u256d"
#define BORDER_TR "\u256e"
#define BORDER_BL "\u2570"
#define BORDER_BR "\u256f"

static bool grid[SIZE][SIZE];

void render() {
    printf("\033[2J\033[H");

    printf("%s", BORDER_TL);
    for (uint32_t x = 0; x < SIZE * 2; x++) printf("%s", BORDER_H);
    printf("%s\n", BORDER_TR);

    for (uint32_t y = 0; y < SIZE; y++) {
        printf("%s", BORDER_V);
        for (uint32_t x = 0; x < SIZE; x++) {
            if (grid[y][x])
                printf("%s", CELL_ALIVE);
            else
                printf("%s", CELL_DEAD);
        }
        printf("%s", BORDER_V);
        printf("\n");
    }

    printf("%s", BORDER_BL);
    for (uint32_t x = 0; x < SIZE * 2; x++) printf("%s", BORDER_H);
    printf("%s\n", BORDER_BR);
}

uint32_t get_alive_neighbors(uint32_t x, uint32_t y, bool grid[SIZE][SIZE]) {
    uint32_t neighbors = 0;

    // Row above
    if (y > 0) {
        if (x > 0) neighbors += grid[y - 1][x - 1];
        neighbors += grid[y - 1][x];
        if (x + 1 < SIZE) neighbors += grid[y - 1][x + 1];
    }
    // Left and right cells
    if (x > 0) neighbors += grid[y][x - 1];
    if (x + 1 < SIZE) neighbors += grid[y][x + 1];
    // Row below
    if (y + 1 < SIZE) {
        if (x > 0) neighbors += grid[y + 1][x - 1];
        neighbors += grid[y + 1][x];
        if (x + 1 < SIZE) neighbors += grid[y + 1][x + 1];
    }

    return neighbors;
}

void update_cell(bool *cell, uint32_t neighbors) {
    if (*cell) {
        // Alive
        if (neighbors < 2 || neighbors > 3) {
            *cell = false;
        }
    } else {
        // Dead
        if (neighbors == 3) {
            *cell = true;
        }
    }
}

void update() {
    static bool grid_copy[SIZE][SIZE];
    memcpy(grid_copy, grid, sizeof(grid));

    for (uint32_t y = 0; y < SIZE; y++) {
        for (uint32_t x = 0; x < SIZE; x++) {
            uint32_t neighbors = get_alive_neighbors(x, y, grid_copy);
            update_cell(&grid[y][x], neighbors);
        }
    }
}

int main() {
    grid[0][0] = true;
    grid[SIZE - 1][SIZE - 1] = true;
    grid[0][SIZE - 1] = true;
    grid[SIZE - 1][0] = true;

    grid[35][32] = true;
    grid[35][33] = true;
    grid[35][34] = true;

    grid[4][5] = true;
    grid[5][6] = true;
    grid[6][4] = true;
    grid[6][5] = true;
    grid[6][6] = true;

    while (true) {
        render();
        update();
        /* usleep(500 * 1000); */
        getc(stdin);
    }

    return 0;
}
