#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile;


    if (infile == NULL)
    {
        printf("%s didn't open!\n", argv[1]);
        return 2;
    }

   unsigned char buffer[512];
   int count = 0;

   char arr[8];                                 // Or can use char filename[8]. (I think) There is Segmentation fault, because when use *filename, memory make space for the string, and ADDITIONAL
   char *filename = arr;                        // 4bytes of memory for the address of the string...


    while (fread(buffer, 512, 1, infile))
    {

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {


            if (count != 0)
            {
                fclose(outfile);
            }
            sprintf(filename, "%03d.jpg", count);
            outfile = fopen(filename, "w");
            count = count + 1;
        }

        if (count != 0)
        {
            fwrite(buffer, sizeof(buffer), 1, outfile);
        }
    }

    fclose(outfile);
    return 0;
}

