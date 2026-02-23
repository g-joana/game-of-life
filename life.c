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

int lives(int w, int a, int s, int d) {

    if ((w + a + s + d) >= 3)
        return 0;

    return 1;
}

int main(int argc, char **argv) {
    if (argc != 4) return 0;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
  //  int iterations = atoi(argv[3]);
    int size = width * height;

    
    int *world = calloc(size, sizeof(int));
    if (!world) return 1;

    draw(world, width, height);

    // iterar
    
    print(world, width, height);
    free(world);
    return 0;
}