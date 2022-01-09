#include <stdio.h>
#include <cs50.h>

void blank_symbol(int height, int row);
void hash_symbol(int row);

int main(void)
{

    int row, height, i;

    // Wait for correct input
    do
    {

        height = get_int("Height: ");

    }
    while (height > 8 || height < 1);


    for (row = 1; row <= height; row++)
    {

        blank_symbol(height, row);
        hash_symbol(row);

        // Loop to create the gap between
        for (i = 0; i < 2; i++)
        {
            printf(" ");
        }

        hash_symbol(row);
        //blank_symbol(height, row);

        printf("\n");
    }
}





// Align the bricks
void blank_symbol(int height, int row)
{
    int i;

    for (i = 0; i < (height - row); i++)
    {
        printf(" ");
    }
}


// Creates a brick
void hash_symbol(int row)
{
    int i;

    for (i = 0; i < row; i++)
    {
        printf("#");
    }

}