#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{//check if the input makes sense
    if(argc != 3)
    {
        fprintf(stdout,"Usage: ./whodunit filereading filewriting");
        return 1;
    }
    char* readfile = argv[1];
    char* writefile = argv[2];
    //open readfile and check if it can be opened.
    
    FILE * in = fopen(readfile, "r");
    if  (in == NULL){
        fprintf(stdout,"%s could not be opened", readfile);
        return 2;
    }
    //make and check if it can be made. if it can't be made, close in.
    FILE * out = fopen(writefile, "w+");
    if  (out == NULL){
        fprintf(stderr,"%s could not be made", writefile);
        fclose(in);
        return 3;
    }
    //read in's bitmapfileheader and bitmapinfoheader to see how big the file is etc
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    fread(&bfh, sizeof(BITMAPFILEHEADER), 1,in);//read "sizeof(BITMAPFILEHEADER)", each of which is one byte long from in to bf.
    fread(&bih, sizeof(BITMAPINFOHEADER), 1,in);//read "sizeof(BITMAPFILEHEADER)", each of which is one byte long from in to bf.
    
    if (bfh.bfType != 0x4d42 || bfh.bfOffBits != 54 || bih.biBitCount != 24)// 0x4D42 = BM in hex, see how long the offset from start of infoheader is, check if bits per pixel is 24, as is the case for bmp's.
    {//
        fclose(out);
        fclose(in);
        fprintf(stderr, "wrong file format.\n");
        return 4;

    }
    //bfOffBits is a DWORD that specifies the offset from the beginning of the BITMAPFILEHEADER structure to the start of the actual bits.
    //The DIB header immediately follows the file header, but the actual image bits need not be placed next to the headers in the file.

    //write out's fileheader and infoheader.
    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, out);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, out);
    
    //maybe we need to add padding to make a multiple of 4
    int padding =  (4 - (bih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //go over in's scanlines.
    for (int i = 0, biHeight = abs(bih.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in each scanline
        for (int j = 0; j < bih.biWidth; j++)
        {
            // temporarily store RGBTRIPLE
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, in);
            if(triple.rgbtRed == 0xff){
                triple.rgbtRed = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtBlue = 0xff;
    }
            
            fwrite(&triple, sizeof(RGBTRIPLE), 1, out);//write triple to out with size of rgbtriple, and only once)
        }

        // skip over padding, if there's any we have added
        fseek(in, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, out);
        }
    }

    // close infile
    fclose(in);

    // close outfile
    fclose(out);

    // that's all folks
    return 0;
}


