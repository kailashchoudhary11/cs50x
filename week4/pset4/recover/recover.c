#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    
    // checking total number of arguments
    
    if (argc != 2)
    {
        printf("Usage Error\n");
        return 1;
    }
    
    // opening the file to read
    
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("File does not exist\n");
        return 1;
    }
    BYTE buffer[512];
    int filecount = 0;
   
    char filename[20];
    FILE *fptr;
    while (1)
    {
        // reading from file
        
        int k = fread(buffer, 1, 512, input);
        
        // closing the file if it is eof
        
        if (k < 512)
        {
            fclose(fptr);
            break;
        }
        
        // checking if it start of new file
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", filecount);
            
            // checking and writing if it is first file
            
            if (filecount == 0)
            {
                fptr = fopen(filename, "w");
                fwrite(buffer, 1, 512, fptr);
                filecount ++;
            }
            
            // closing and opening a new file if it is not first file
            
            else
            {
                fclose(fptr);
                fptr = fopen(filename, "w");
                fwrite(buffer, 1, 512, fptr);
                filecount ++;
            }
        }
        
        // writing in the same file if it is not a start of new file
        
        else
        {
            fwrite(buffer, 1, 512, fptr);
        }
        
    }
    
    fclose(input);
}