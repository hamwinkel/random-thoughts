#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{

    char screen[10,10];

    screen [0,0] = 1;
    screen [0,9] = 2;
    screen [9,0] = 3;
    screen [9,9] = 4;

    int x = 0,
        y = 0;

    while (y < 10){
        if (y = 9) printf("\n")
        else putchar = screen [x, y];
        while (x < 10){
            if (x != '\0'){
                putchar(screen[x, y]);
            }
            else if (x = 9) printf("\n");
            x++;
        }
    y++;
    }
return 0;
}
