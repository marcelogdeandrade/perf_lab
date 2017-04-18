#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "image_proc.h"

void rotate_image(image_t *src, image_t *dest) {
  int i, j;
  pixel_t pix;
  for (i = 0; i < src->nrows; i++) {
    for (j = 0; j < src->ncols; j++) {
      pix = get_pix(src, i, j);
      set_pix(dest, dest->nrows - j - 1, i, pix);
    }
  }
}

void better_rotate_image(image_t *src, image_t *dest) {
  int n, block_size;
  n = src->nrows;
  block_size = 32;
  pixel_t* src_pixel = src->data;
  pixel_t* dest_pixel = dest->data;
  for (int i = 0; i < n; i += block_size) {
    for (int j = 0; j < n; j += block_size) {
      for (int k = i; k < i + block_size; k++){
        for (int l = j; l < j + block_size; l++){
          int col_src = l * n;
          int index_dest = (n - 1 - k) * n + l;
          int index_src = col_src + k;
          dest_pixel[index_dest] = src_pixel[index_src];
        }
      }
    }
  }
}

float avg_luma(image_t *img) {
  int i, j;
  double luma;
  pixel_t pix;
  luma = 0.0;
  for (i = 0; i < img->nrows; i++) {
    for (j = 0; j < img->ncols; j++) {
      pix = get_pix(img, i, j);
      luma += 0.299 * ((double) pix.c[0]) +
              0.587 * ((double) pix.c[1]) +
              0.114 * ((double) pix.c[2]);
    }
  }
  luma /= (double) (img->nrows * img->ncols);

  return (float) luma;
}

float better_avg_luma(image_t *img) {
  int n;
  n = img->ncols;
  n *= n;
  float luma;
  int r,g,b;
  pixel_t pix;
  r = 0;
  g = 0;
  b = 0;
  for (int i = 0; i < (n - 7); i += 8) {
    pix = img->data[i];
    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 1];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );


    pix = img->data[i + 2];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 3];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 4];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 5];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 6];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );

    pix = img->data[i + 7];

    r = r + (pix.c[0] );
    g = g + (pix.c[1] );
    b = b + (pix.c[2] );
  }

  r = r * 0.299;
  g = g * 0.587;
  b = b * 0.114;
  luma = r + g + b;
  luma = luma / n;
  return luma;
}
