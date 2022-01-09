#include "helpers.h"
#include <math.h>
#include <stdio.h>

int outside(int x, int y, int width, int height)
{
    if (x < 0)
    {
        return 1;
    }

    if (x >= height)
    {
        return 1;
    }

    if (y < 0)
    {
        return 1;
    }

    if (y >= width)
    {
        return 1;
    }

    return 0;
}

typedef struct
{
    int  rgbtBlue;
    int  rgbtGreen;
    int  rgbtRed;
}
RGB_SUM;//This struct is used by blur function, because RGBTRIPLE size limitation

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = round((float)(image[x][y].rgbtRed + image[x][y].rgbtGreen + image[x][y].rgbtBlue) / 3);
            image[x][y].rgbtGreen = image[x][y].rgbtRed;
            image[x][y].rgbtBlue = image[x][y].rgbtRed;
        }
    }
    return;
} //Done

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rgb; //A temporary pixel
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width / 2; y++)
        {
            rgb = image[x][(width - 1) - y];
            image[x][(width - 1) - y] = image[x][y];
            image[x][y] = rgb;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGB_SUM sum; // Calculate sum color amount
    RGBTRIPLE image_copy[height][width];

    int coord_x, coord_y;
    int n; //number of taken pixels
    int cx[] = {0, +1, +1, 0, -1, -1, -1, 0, +1};
    int cy[] = {0, 0, +1, +1, +1, 0, -1, -1, -1};


    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image_copy[x][y] = image[x][y];
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            n = 0;
            sum.rgbtRed = 0;
            sum.rgbtGreen = 0;
            sum.rgbtBlue = 0;
            for (int c = 0; c < 9; c++)
            {
                coord_x = x + cx[c];
                coord_y = y + cy[c];
                //x {0, +1, +1, 0, -1, -1, -1, 0, +1};
                //y {0, 0, +1, +1, +1, 0, -1, -1, -1};
                if (outside(coord_x, coord_y, width, height) == 1) //Check is it outside of the picture
                {
                    continue;
                }


                n++;
                sum.rgbtRed = sum.rgbtRed + image[coord_x][coord_y].rgbtRed;
                sum.rgbtGreen = sum.rgbtGreen + image[coord_x][coord_y].rgbtGreen;
                sum.rgbtBlue = sum.rgbtBlue + image[coord_x][coord_y].rgbtBlue;
            }

            image_copy[x][y].rgbtRed = round((float)sum.rgbtRed / n);
            image_copy[x][y].rgbtGreen = round((float)sum.rgbtGreen / n);
            image_copy[x][y].rgbtBlue = round((float)sum.rgbtBlue / n);
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = image_copy[x][y];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGB_SUM Gx, Gy, color; // Calculate sum color amount
    RGBTRIPLE image_copy[height][width];

    int cx[] = {0, +1, +1, 0, -1, -1, -1, 0, +1}; // This are the cordinates of the pixels, that surounds the
    int cy[] = {0, 0, +1, +1, +1, 0, -1, -1, -1}; // (x,y) pixel;

    int x_mask[] = {0, 0, 1, 2, 1, 0, -1, -2, -1}; //Convolution matrix (mask) for x direction
    int y_mask[] = {0, -2, -1, 0, 1, 2, 1, 0, -1}; //Convolution matrix (mask) for y direction

    int coord_x, coord_y;
    int n; //number of taken pixels

    //width = height = 3;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            Gx.rgbtRed = 0;
            Gx.rgbtGreen = 0;
            Gx.rgbtBlue = 0;

            Gy.rgbtRed = 0;
            Gy.rgbtGreen = 0;
            Gy.rgbtBlue = 0;
            for (int c = 0; c < 9; c++)
            {
                coord_x = x + cx[c];
                coord_y = y + cy[c];

                if (outside(coord_x, coord_y, width, height) != 1)
                {
                    Gx.rgbtRed = Gx.rgbtRed + image[coord_x][coord_y].rgbtRed * x_mask[c];
                    Gx.rgbtGreen = Gx.rgbtGreen + image[coord_x][coord_y].rgbtGreen * x_mask[c];
                    Gx.rgbtBlue = Gx.rgbtBlue + image[coord_x][coord_y].rgbtBlue * x_mask[c];

                    Gy.rgbtRed = Gy.rgbtRed + image[coord_x][coord_y].rgbtRed * y_mask[c];
                    Gy.rgbtGreen = Gy.rgbtGreen + image[coord_x][coord_y].rgbtGreen * y_mask[c];
                    Gy.rgbtBlue = Gy.rgbtBlue + image[coord_x][coord_y].rgbtBlue * y_mask[c];

                    //printf("-%d", image[coord_x][coord_y].rgbtRed);
                }



            }
            //printf("\n\n");
            //printf("%d %d\n", Gx.rgbtRed, Gy.rgbtRed);

            color.rgbtRed = round(sqrt((Gx.rgbtRed * Gx.rgbtRed) + (Gy.rgbtRed * Gy.rgbtRed)));
            color.rgbtGreen = round(sqrt((Gx.rgbtGreen * Gx.rgbtGreen) + (Gy.rgbtGreen * Gy.rgbtGreen)));
            color.rgbtBlue = round(sqrt((Gx.rgbtBlue  * Gx.rgbtBlue) + (Gy.rgbtBlue  * Gy.rgbtBlue)));

            //printf("%d\n\n", color.rgbtRed);
            if (color.rgbtRed >= 255)
            {
                color.rgbtRed = 255;
            }

            if (color.rgbtGreen >= 255)
            {
                color.rgbtGreen = 255;
            }

            if (color.rgbtBlue >= 255)
            {
                color.rgbtBlue = 255;
            }

            image_copy[x][y].rgbtRed = color.rgbtRed;
            image_copy[x][y].rgbtGreen = color.rgbtGreen;
            image_copy[x][y].rgbtBlue = color.rgbtBlue;

        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = image_copy[x][y];
        }
    }


    return;
}