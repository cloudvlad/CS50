#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int p, e, y = 0;
    /*
    p - population
    e - end polulation
    t - time
    */

    // Wait for correct value for starting
    do
    {
        p = get_int("Start size: ");
    }
    while (p < 9);

    // Wait for correct value for ending
    do
    {
        e = get_int("End size: ");
    }
    while (e < p);

    // Change population
    while (p < e)
    {
        p = p + (p / 3) - (p / 4);
        y = y + 1;
    }


    printf("Years: %i\n", y);
    return 0;
}