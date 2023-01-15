#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    int BLOCK_SIZE = 512;
    char *filename = malloc(8);
    int counter = 0;
    BYTE buffer[512];
    FILE *img;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
                counter++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
                counter++;
            }
        }
        else if (counter == 0)
        {
            continue;
        }
        else
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);

        }
    }
    free(filename);
    fclose(file);
    fclose(img);
}