#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void draw(int *world, int width, int height) {
    
    int x = 0;
    int y = 0;
    int lock = 1;
    int c;

    while (read(0, &c, 1) > 0) {

        if (c == 'w')
            y--;
        else if (c == 'a')
            x--;
        else if (c == 's')
            y++;
        else if (c == 'd')
            x++;
        else if (c == 'x')
            lock = 0;
        
        if (x < 0 || x >= width || y < 0 || y >= height)
            break;
        
        if (!lock)
            world[y * width + x] = 1;
    }
}


int lives(int w, int a, int s, int d) {
    if ((w + a + s + d) >= 3)
        return 0;
}

int main (int argc, char **argv) {

    if (!(argv[1] && argv[2] && argv[3]) || (argc > 4))
        return 0;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    int size = width * height;
    int iterations = atoi(argv[3]);

    int world[size];
    for (int i = 0; i < size; i++) {
        world[i] = 0;
       // printf("%i", i);
    }

    draw(world, width, height);

    for (int i = 0; i < size; i++) {
        if (world[i] == 1)
            printf("o");
        else if (world[i] == 0)
            printf(" ");
        if((i + 1) % width == 0)
            printf("\n");
    }
}