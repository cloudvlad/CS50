// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Custom types
typedef uint8_t BYTE;
typedef int16_t WORD;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    BYTE buffer;
    int header_counter = 0;

    while (fread(&buffer, sizeof(BYTE), 1, input))
    {
        header[header_counter] = buffer;
        header_counter = header_counter + 1;

        if (header_counter == HEADER_SIZE)
        {
            break;
        }
    }
    fwrite(header, sizeof(BYTE), HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    WORD sample;

    while (fread(&sample, sizeof(WORD), 1, input))
    {
        sample = sample * factor;
        fwrite(&sample, sizeof(WORD), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
