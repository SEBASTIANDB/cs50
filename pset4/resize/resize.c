/**
 * resizes a bmp by n
 * It was colonel mustard with the candlestick in the library
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize scale infile outfile\n");
        return 1;
    }
    
    // store scale
    int scale = atoi(argv[1]);
       
    // make sure scale is is between 0 and 100
    if( scale < 1|| scale > 100)
    {
        printf("Scale must be a between 1 and 100\n");
        return 1;
    }

    // store filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not make %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // check if it's the right kind of file
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || //BM, etc
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    } 
    
    int widthOriginal = bi.biWidth;// store original width and height
    int heightOriginal = bi.biHeight;
    
    bi.biWidth *= scale;// update width and height
    bi.biHeight *= scale;
    
    int paddingOriginal =  (4 - (widthOriginal * sizeof(RGBTRIPLE)) % 4) % 4;// calculate paddings for the scanlines
    int paddingNew =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + paddingNew);// update image size
    
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER); // update file size
    
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));// allocate memory for every stored scanline
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);// write outfile's BITMAPFILEHEADER
    
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);// write outfile's BITMAPINFOHEADER
    
    for (int i = 0, biHeight = abs(heightOriginal); i < biHeight; i++)// iterate over infile's rows(scanlines)    
    {
        int place = 0;
        for (int j = 0; j < widthOriginal; j++)// iterate over pixels in every scanline
        {
            RGBTRIPLE triple;// store RGBTRIPLE
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // write pixel to buffer n times
            for(int count = 0; count < scale; count++)
            {
                *(buffer+(place)) = triple;
                place++;
            }
        }//
            
        
        fseek(inptr, paddingOriginal, SEEK_CUR);// skip over padding(if there is padding at all)
        
           for(int r = 0; r < scale; r++)// write RGBTRIPLE to outfile
           {
                fwrite((buffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);
                //adding padding to newfile if necessary
                for (int k = 0; k < paddingNew; k++)
                    fputc(0x00, outptr);
           }        
    }
    fclose(inptr);// close infile
    fclose(outptr);// close outfile
    free(buffer);// free all memory
    // success
    return 0;
}