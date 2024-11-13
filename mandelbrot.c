#include "mandelbrot.h"
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define REAL_INTERVAL_LEFT -2
#define REAL_INTERVAL_RIGHT 1
#define IMAGINARY_INTERVAL_LEFT 1
#define IMAGINARY_INTERVAL_RIGHT -1
#define RADIUS 2

//calculateMandelbrotSet: la funzione prende in input il puntatore all'immagine, larghezza, altezza e numero di iterazioni.
//			  Calcola l'incremento per x e y in base alla larghezza/altezza e agli intervalli specificati.
//			  Per ogni pixel dell'immagine, crea un numero complesso associato usando gli incrementi,
//			  calcola l'intensità del pixel con isInMandelbrotSet() e cambia il pixel con il numero
//			  appena calcolato
void calculateMandelbrotSet(netpbm_ptr image, int width, int height, int iterations)
{
    float realIncrement = (abs(REAL_INTERVAL_LEFT) + abs(REAL_INTERVAL_RIGHT)) / (float)width;
    float imaginaryIncrement = (abs(IMAGINARY_INTERVAL_LEFT) + abs(IMAGINARY_INTERVAL_RIGHT)) / (float)height;
    
    //Mapping complex numbers
    #pragma omp parallel
    {
	#pragma omp for schedule(dynamic,1)
	for(int currImageX = 0; currImageX < width; currImageX++)
	{
	    for(int currImageY = 0; currImageY < height; currImageY++)
	    {
		float complex c = CMPLX(REAL_INTERVAL_LEFT + currImageX * realIncrement, IMAGINARY_INTERVAL_LEFT - currImageY * imaginaryIncrement);
		int n = isInMandelbrotSet(c, iterations);
		char * pixel = pixel_at(image, currImageX, currImageY);
		*pixel = (char)(255 * (log(n)/log(iterations)));
	    }
	}
    }
}

//isInMandelbrotSet: La funzione prende in input un numero complesso piu il numero di iterazioni, e ritorna
//		     il numero di iterazioni fatte prima che la condizione nel blocco if venga soddisfatta,
//		     altrimenti ritorna il valore di iterazioni fortnito in input
//		     La funzione usa la definizione di successione di Mandelbrot per calcolare i valori necessari
int isInMandelbrotSet(float complex c, int iterations)
{
    float complex num = CMPLX(0.0, 0.0);
    for(int i = 1; i <= iterations; i++)
    {
	num = cpow(num, 2) + c;
	if(cabs(num) >= RADIUS)
	{
	    return i;
	}
    }
    return iterations;
}
