#include <stdio.h>
#include <string.h>
#define HEADER_SIZE 54

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #2
    NetID: 1260340
*/

// This method turns an image into sepia. 
void createSepia( int width, int height, unsigned char[][width * 3]); 

// This method flip the image horizontally 
void mirrorHorizontal(int width, int height, unsigned char[] [width *3]); 

// This method rotates the image in 180 degree
void rotate180(int width, int height, unsigned char[] [width *3]);

// This method blurred the image. 
void createBlurred(int width, int height, unsigned char[] [width *3]);

// This method turns an image to black and white. (Extra credit)
void blackAndWhite(int width, int height, unsigned char[] [width *3]);

// This method invert the original image. (Extra credit)
void invert(int width, int height,unsigned char[] [width *3]);

/* This is the main method */
int main(void) {
    int i = 0, j = 0;
     int height =0, width = 0;
    char fileName[256]; 
    printf("Enter the filename: ");
    scanf("%s", fileName);
    strcat(fileName, ".bmp");
    // need to append .bmp file name

    printf("Enter height and width (in pixels) : ");
    scanf(" %d %d", &height, &width); 
   
    // open the file
    FILE *infile = fopen(fileName, "rb"); 
    FILE *outfile1 = fopen("copy1.bmp", "wb"); 
    FILE *outfile2 = fopen("copy2.bmp", "wb"); 
    FILE *outfile3 = fopen("copy3.bmp", "wb"); 
    FILE *outfile4 = fopen("copy4.bmp", "wb");
    FILE *outfile5 = fopen("copy5.bmp", "wb");
    FILE *outfile6 = fopen("copy6.bmp", "wb");

    char header[HEADER_SIZE]; 
    unsigned char pixels[height][width * 3];
    unsigned char pixels1[height][width * 3];

    // read the input file
    fread( header, 1 , HEADER_SIZE , infile);
    fread( pixels, 1 , height * width * 3 , infile);
    
    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels));
    // output a copy of the original in sepia
    createSepia(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile1);
    fwrite( &pixels1, sizeof(char)  , height * width * 3  ,  outfile1);

    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels)); 
    // blur the image by averaging the value with its surrounding values. 
    createBlurred(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile2);
    fwrite( &pixels1, sizeof(char)  , height * width * 3  ,  outfile2);


    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels)); 
    // a copy of the original mirrored horizontally
    mirrorHorizontal(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile3);
    fwrite( &pixels1, sizeof(char)  , height * width * 3  ,  outfile3);

    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels)); 
    // a copy of the original 180 rotated image
    rotate180(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile4);
    fwrite( &pixels1, sizeof(char)  , height * width * 3  ,  outfile4);


    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels)); 
    // a copy of the black and white image. 
    blackAndWhite(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile5);
    fwrite( &pixels1, sizeof(char)  , height * width * 3  ,  outfile5);

    // make copies of the 2D array pixels
    memcpy(pixels1, pixels, sizeof(pixels)); 
    // a copy of the inverted image. 
    invert(width, height, pixels1);
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile6);
    fwrite( &pixels1, sizeof(char)  , height * width * 3 ,  outfile6);

    printf("Done. Check the generated images.\n");

    // close all files
    fclose(infile);
    fclose(outfile1);
    fclose(outfile2);
    fclose(outfile3);
    fclose(outfile4);
    fclose(outfile5);
    fclose(outfile6);
    return 0;
}


/*This method creates an inverted image */
void invert(int width, int height, unsigned char thePixels[][width*3]) {
    int i, j = 0; 
    for(i = 0; i < height -1; i++) {
        for(j = 0; j < width *3; j++) {
            thePixels[i][j] = 255 -thePixels[i][j];
        }
    }
}


/* This method blurred the image */
void createBlurred(int width, int height, unsigned char thePixels[][width*3]) {
    int i, j = 0; 
    unsigned char avg; 
    for(i = 1; i < height - 1; i++) {
        for(j = 1; j < width *3 -1; j++) {
            avg = (thePixels[i-1][j-3] + thePixels[i-1][j] + thePixels[i-1][j+3] + thePixels[i][j-3] + thePixels[i][j] + thePixels[i][j+3] + thePixels[i+1][j-3] + thePixels[i+1][j] + thePixels[i+1][j+3]) / 9; 
            thePixels[i][j] = avg; 
        }
    }
}

/* This method creates a black and white image */
void blackAndWhite(int width, int height, unsigned char thePixels[][width*3]) {
    int i, j = 0; 
    unsigned char avg; 
    for(i = 0; i < height - 1; i++) {
        for(j = 0; j < width *3 -1; j++) {
            avg = (thePixels[i-1][j-1] + thePixels[i-1][j] + thePixels[i-1][j+1] + thePixels[i][j-1] + thePixels[i][j] + thePixels[i][j+1] + thePixels[i+1][j-1] + thePixels[i+1][j] + thePixels[i+1][j+1]) / 9; 
            thePixels[i][j] = avg;
        }
    }
}

/* This method rotate image 180 degrees */
void rotate180(int width, int height, unsigned char thePixels[][width*3]) {
    int i, j = 0;
    unsigned char tempB, tempG, tempR = 0; 
    for(i = 0; i < height/2; i++) {
        for (j = 0; j < width*3; j+=3) {
            tempR = thePixels[height-1 -i][(width *3)-1 - j];
            tempG = thePixels[height-1 -i][(width *3)-2 - j];
            tempB = thePixels[height-1 -i][(width *3)-3 - j];

            thePixels[height-1 -i][(width *3)-1 -j] = thePixels[i][j+2]; // R
            thePixels[height-1 -i][(width *3)-2 -j] = thePixels[i][j+1]; // G
            thePixels[height-1 -i][(width *3)-3-j] = thePixels[i][j];   // B

            thePixels[i][j+2] = tempR;
            thePixels[i][j+1] = tempG;
            thePixels[i][j] = tempB;
        }
    }
}

/* This method flip the image in a horizontal fashion. */
void mirrorHorizontal(int width, int height, unsigned char pixels1[][width*3]) {
    
   int i, j = 0;
   for(j = 0; j < height; j++) {
        for(i = 0; i < (width * 3)/ 2; i+=3) {
            pixels1[j][(width * 3) -1 - i] = pixels1[j][i+2] ;
	    pixels1[j][(width * 3) -2 - i] = pixels1[j][i+1];
	    pixels1[j][(width * 3) -3- i] = pixels1[j][i];
        }
    }
}

/* This method creates sepia */ 
void createSepia(int width, int height, unsigned char pixels1[][width *3]) {
   // make copies of the 2D array pixels
   
    int i, j = 0; 
    unsigned char tempB, tempG, tempR; 
    for(i = 0; i < height; i++) {
        for(j = 0; j < width *3; j+=3) {
            unsigned char newBlue = pixels1[i][j];
            unsigned char newGreen = pixels1[i][j+1];
            unsigned char newRed = pixels1[i][j+2];

            if(newBlue * 0.131 + newGreen * 0.534 + newRed * 0.272 > 255) {
                tempB = 255;
            } else {
                tempB = newBlue * 0.131 + newGreen * 0.534 + newRed * 0.272; 
            }

            if(newBlue * 0.168 + newGreen * 0.686 + newRed * 0.349 > 255) {
                tempG = 255;
            } else {
                tempG = newBlue * 0.168 + newGreen * 0.686 + newRed * 0.349; 
            }

            if(newBlue * 0.189 + newGreen * 0.769 + newRed * 0.393 > 255) {
                tempR = 255;
            } else {
                tempR = newBlue * 0.189 + newGreen * 0.769 + newRed * 0.393; 
            }

            pixels1[i][j] = tempB;
            pixels1[i][j+1] = tempG;
            pixels1[i][j+2] = tempR; 

        }
    }
} 





