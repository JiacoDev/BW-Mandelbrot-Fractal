# Mandelbrot Image Generator in PGM

This project was created as part of a university exam. It generates images of the Mandelbrot set in PGM (Portable Gray Map) format and utilizes OpenMP to accelerate calculations on multi-threaded systems.

## Code Structure

The main code is in `main.c` and includes the following libraries:

- `pgm.h`: Manages image handling in the PGM format.
- `mandelbrot.h`: Computes the Mandelbrot set.
- `omp.h`: OpenMP library for parallel processing.

The program accepts as input the output file name, the maximum number of iterations, and the image width (columns). The number of rows is automatically calculated to maintain a 3:2 aspect ratio.

## Requirements

- C compiler (e.g., GCC)
- OpenMP library (included in recent versions of GCC)
- Header files `pgm.h` and `mandelbrot.h` with their respective implementations.

Ensure all necessary files are in the project directory before compiling.

## Compilation

To compile the project, simply download it, navigate to the project directory, and use:

```bash
git clone https://github.com/JiacoDev/BW-Mandelbrot-Fractal.git ./Mandelbrot-frac-image-gen
cd ./Mandelbrot-frac-image-gen
make
```

## Execution

Once compiled, run the program using the following syntax:

```bash
./main <output_file_name> <max_iterations> <width>
```

## Parameters

- `output_file_name`: The base name of the output file (the .pgm extension is added automatically).
- `max_iterations`: Maximum number of iterations for each pixel in the Mandelbrot set.
- `width`: Number of columns (pixels) in the output image. The number of rows is calculated automatically to keep a 3:2 aspect ratio.

## Example
```bash
./main mandelbrot_image 1000 800
```

This command generates a Mandelbrot image with:

- File name: `mandelbrot_image.pgm`
- Maximum 1000 iterations per pixel
- 800 columns (width) and 1200 rows (height).

## Output
The program saves the generated image as a `.pgm` file in the current directory and prints the execution time to the console.
