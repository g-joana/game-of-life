#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int lives(int left, int up, int right, int down) {
    
}

int main (int argc, char **argv) {

    if (!(argv[1] && argv[2] && argv[3]) || (argc > 4))
        return 0;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    int size = width * height;
    int iterations = atoi(argv[3]);

    int *world;
    world = malloc(sizeof(int) * size);
    int lock_pen = 0;

    for (int i = 0; i < size; i++) {
        world[i] = 0;
        printf("%i\n", i);
    }

    int lock = 0;
    int x = 0;
    int y = 0;

    char c;
    while (read(0, &c, 1) > 0) {
        if (c == 'a') {
            x++;
        }
        else if (c == 'd') {
            x++;
        }
        else if (c == 's') {
            y++;
        }
        else if (c == 'w') {
            y--;
        }
        else if (c == 'x') {
            lock = false;
        }
        if (!lock)
            world[x*y] = 1;

        if ((y >= height) || (x >= width))
            break; 
    }

    while (i < size) {

        world[i] = 0;
        printf("%i\n", i);
    }



}