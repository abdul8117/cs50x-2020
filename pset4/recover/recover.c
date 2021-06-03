#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // validate user input
    if (argc != 2)
    {
        printf("Usage: ./recover image.raw");
        return 1;
    }

    FILE *fpointer = fopen(argv[1], "r");
    if (fpointer == NULL)
    {
        printf("File does not exist.");
        return 1;
    }

    // buffer to hold the file content in memory
    BYTE buffer[512];

    char filename[8];
    int img_counter = 0;
    FILE *img;

    while (fread(&buffer, sizeof(BYTE), 512, fpointer) == 512)
    {
        // check if jpeg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if first jpeg
            if (img_counter == 0)
            {
                // create a file for the jpeg
                sprintf(filename, "%03i.jpg", img_counter);
                img = fopen(filename, "a");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                img_counter++;
            }
            else
            {
                //
                fclose(img);
                sprintf(filename, "%03i.jpg", img_counter);
                img = fopen(filename, "a");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                img_counter++;
            }
        }
        else
        {
            // image continues on as there is no jpeg header
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }
    }
}
