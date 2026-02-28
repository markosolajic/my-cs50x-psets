// Author: Marko Solajic

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Program requires exactly one argument - the memory card filename
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // If it fails to open the card
    if (card == NULL)
    {
        printf("Failed to open %s!\n", argv[1]);
        return 1;
    }

    // Create a buffer for a 512 byte block of data
    uint8_t buffer[BLOCK_SIZE];

    char filename[8]; // "000.jpg" = 7 chars + null terminator
    FILE *img = NULL; // NULL means no JPEG is currently being written
    int counter = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, BLOCK_SIZE, 1, card) == 1)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If img is already open
            if (img != NULL)
            {
                fclose(img);
            }

            // Build filename like 000.jpg, 001.jpg etc.
            sprintf(filename, "%03i.jpg", counter);

            img = fopen(filename, "w");

            // If it fails to open the file
            if (img == NULL)
            {
                printf("Failed to open %s!\n", filename);
                fclose(card);
                return 1;
            }

            // Increment after opening so first file is 000.jpg, second 001.jpg etc.
            counter++;
        }

        // Write 512 bytes to the current JPEG if one is open
        if (img != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}
