#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void print(int *world, int width, int height) {

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (world[y * width + x])
                putchar('O');
            else
                putchar(' ');

        }
        putchar('\n');
    }
}

void draw(int *world, int width, int height) {

    int x = 0, y = 0, drawing = 0;
    char c;

    while (read(0, &c, 1) > 0) {

        if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < height - 1) y++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'd' && x < width - 1) x++;

        else if (c == 'x') drawing = !drawing;

        if (drawing)
            world[y * width + x] = 1;
    }
}

int count_neighbors(int *world, int x, int y, int width, int height) {
    
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) continue;

            int ny = y + i;
            int nx = x + j;

            if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                if (world[ny * width + nx])
                    count++;
            }
        }
    }
    return count;
}

int lives(int cell, int population) {

    if (population == 3)
        return 1;
    if (population == 2 && cell)
        return 1;

    return 0;
}

int main(int argc, char **argv) {

    if (argc != 4) return 1;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    int size = width * height;

    
    int *world = calloc(size, sizeof(int));
    if (!world) return 1;

    draw(world, width, height);

    print(world, width, height);
    usleep(300000);

    for (int i = 0; i < iterations; i++) {

        int *next_gen = calloc(size, sizeof(int));
        if (!next_gen) return 1;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                int neighbors = count_neighbors(world, x, y, width, height);
                next_gen[y * width + x] = lives(world[y * width + x], neighbors);

            }
        }

        for (int j = 0; j < size; j++)
            world[j] = next_gen[j];

        free(next_gen);

        printf("\033[%dA", height);
        print(world, width, height);
        usleep(300000);
    }
    free(world);
    return 0;
}