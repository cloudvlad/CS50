#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = NULL;

    if (infile == NULL)
    {
        printf("Not enough memory.\n");
        return 2;
    }

    char filename[8];
    BYTE buffer[512];
    int file_counter = 0;

    // Read while it is possible
    while (fread(buffer, 512, 1, infile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            if (file_counter != 0)
            {
                fclose(outfile);
            }
            sprintf(filename, "%03i.jpg", file_counter);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                return 5;
            }
            file_counter++;
        }
        if (file_counter != 0)
        {
            fwrite(buffer, 512, 1, outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
    return 0;
}