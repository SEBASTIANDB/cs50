#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{   
    // open the file programmatically with fopen
    FILE *file = fopen(argv[1], "r");
    if(argc != 2){
        fprintf(stderr,"need only one command line argument");
        return 1;
    }
    
    // check file permission
    if (file == NULL)
    {
        fprintf(stderr, "unable to recover file from card.raw \n");
        return 1;
    }
    
    //size of a block which is 512 bytes
    int size = 512;
    
    // a buffer of 512 bytes
    BYTE buffer[size];
    
    // temp file output, here we put our jpgs.
    FILE* temp = NULL; 
    
    // decimal number for the titles of the jpgfiles
    char names[10]; 
    
    // counter
    int counter = 0; 
    
    
    // until end of file is reached
    while (!feof(file))
    {
       
        // check if it's the start of a new jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if already exist, then close file
            if (temp != NULL)
            {
                fclose(temp);
                
            }
            
            // retitle the file
            sprintf(names, "%03d.jpg", counter);
            
            // re open the file
            temp = fopen(names, "w");
            
            // bump the counter up
            counter++;
            
            // write to file
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        else if (counter > 0)
        {
            // add jpgs to file
            fwrite(buffer, sizeof(buffer), 1, temp);            
            
        }
      
        fread(buffer, sizeof(buffer), 1, file);
        
    }
  
    
    // close the file
    fclose(file);

    // end of program
    return 0;
}