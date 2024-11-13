#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "pgm.h"

// open_image: Apre un'immagine Netpbm specificata dal percorso e la mappa in memoria usando mmap
int open_image(char * path, netpbm_ptr img)
{
  img->fd = fopen(path, "r+");
  if (img->fd == NULL) {
    return -1;
  }
  struct stat sbuf;
  stat(path, &sbuf);
  img->size = sbuf.st_size;
  if (fscanf(img->fd, "P5\n%d %d\n255\n", &img->width, &img->height) != 2) {
    fclose(img->fd);
    return -2;
  }
  img->offset = ftell(img->fd);
  img->data = mmap((void *)0, img->size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(img->fd), 0);
  if (img->data == MAP_FAILED) {
    fclose(img->fd);
    return -3;
  }
  return 0;
}

// empty_image: Crea un'immagine Netpbm vuota con le dimensioni specificate
int empty_image(char * path, netpbm_ptr img, int width, int height)
{
  FILE * fd = fopen(path, "w+");
  if (fd == NULL) {
    return -1;
  }
  int written = fprintf(fd, "P5\n%d %d\n255\n", width, height);
  ftruncate(fileno(fd), written + width * height);
  fclose(fd);
  return open_image(path, img);
}

//pixel_at: Restituisce un puntatore al pixel alla posizione specificata nell'immagine
char * pixel_at(netpbm_ptr img, int x, int y)
{
  if (img == NULL) {
    return NULL;
  }
  if (x < 0 || x >= img->width || y < 0 || y >= img->height) {
    return NULL; 
  }
  return &img->data[y * img->width + x + img->offset]; 
}

//close_image: Chiude l'immagine Netpbm e rilascia le risorse allocate
int close_image(netpbm_ptr img)
{
  if (img == NULL) {
    return -1;
  }
  munmap(img->data, img->size);
  fclose(img->fd);
  return 0; 
}

