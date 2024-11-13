#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include "mandelbrot.h"
#include <time.h>
#include <omp.h>

int main(int argc, char * argv[])
{
    char * fileName = argv[1];
    int nIter, nCols, nRows;
    nIter = atoi(argv[2]);
    nCols = atoi(argv[3]);
    nRows = nCols * 3/2;
    netpbm image;
    strcat(fileName,".pgm");
   
    if(empty_image(fileName, &image, nRows, nCols) != 0)
    {
	printf("Errore nella creazione del file");
    }
    
    double start = omp_get_wtime();
    calculateMandelbrotSet(&image, nRows, nCols, nIter);
    double end = omp_get_wtime();
    printf("%f", (end - start));

    close_image(&image);
}
