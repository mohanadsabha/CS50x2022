#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check that the argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file for reading
    FILE *inputfile = fopen(argv[1], "r");

    // Check that the inputfile is vaild
    if (inputfile == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    // Store blocks of 512 bytes in an array
    unsigned char buffer[512];

    // Track number of images generated
    int count_image = 0;

    // File pointer to recover images
    FILE *outputfile = NULL;

    // char filename[8]
    char *filename = malloc(8 * sizeof(char));

    // read the blocks of 512 bytes
    while (fread(buffer, sizeof(char), 512, inputfile))
    {
        // Check if bytes indicate start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Write the JPG filenames
            sprintf(filename, "%03i.jpg", count_image);

            // Open output file for writing
            outputfile = fopen(filename, "w");

            // Count number of Images found
            count_image++;
        }
        if (outputfile != NULL)
        {
            fwrite(buffer, sizeof(char), 512, outputfile);
        }
    }
    free(filename);
    fclose(inputfile);
    fclose(outputfile);
}