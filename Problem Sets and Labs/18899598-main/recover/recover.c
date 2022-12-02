#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
typedef enum {false, true} bool;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check if only one argument is present
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Check if file can be opened
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }


    BYTE buffer[512]; //Initialize buffer for storing blocks of 512 bytes
    int count = -1;
    FILE *new_file = NULL; //Initialise file to store the recovered jpg files.

    //To extract data by detecting jpg files
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        bool start = false;

        // To check the starting 4 bytes of data of a jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                //Set status true if jpg initial bytes are found and increase count
                start = true;
                count++;

            }
        }

        //Initialise file name to be given to each recovered jpg file
        char *file_name = malloc(sizeof(char) * 8);

        //If new jpg is found
        if (start == true)
        {
            if (count != 0)
            {
                fclose(new_file);
            }

            //Initialise new file name
            sprintf(file_name, "%03i", count);
            strcat(file_name, ".jpg");
            new_file = fopen(file_name, "w");
            //fwrite(buffer, 1, BLOCK_SIZE, new_file);
        }
        free(file_name); // Free the memory

        // If a file is open write the data to the file.
        if (new_file != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, new_file);
        }

    }

    //Close all files
    fclose(raw_file);
    fclose(new_file);
    return 0;
}