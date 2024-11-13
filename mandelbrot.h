#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#include <stdio.h>
#include <complex.h>
#include "pgm.h"

void calculateMandelbrotSet(netpbm_ptr image, int width, int height, int iterations);

int isInMandelbrotSet(float complex c, int iterations);

#endif
