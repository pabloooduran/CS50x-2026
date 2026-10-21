#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Only one command-line argument\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    int count = 0;
    FILE *img = NULL;

    while (fread(buffer, BLOCK_SIZE, 1, file))
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }

        if (img != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(file);
}
