#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    BYTE buffer[512];
    char *filename = malloc(8);
    int filecount = 0;
    FILE *img = NULL;
    int bytecount = 512;

    while (bytecount == 512)
    {
        bytecount = fread(buffer, sizeof(BYTE), 512, file);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (filecount != 0)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", filecount);
            filecount++;
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
        else if (filecount != 0)
        {
            if (bytecount == 512)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            else
            {
                fwrite(buffer, sizeof(BYTE), bytecount, img);
            }
        }

    }

    fclose(img);

}
