
#include <SDL.h>

#include "spiral.h"
#include "graphics.h"

static unsigned couleur = 0x00F0F0FF; // Cyan

static void spiral (int x, int y, int pas, int nbtours)
{
  int i = x, j = y, tour;
  
  for (tour = 1; tour <= nbtours; tour++) {
    for (; i < x + tour*pas;i++)
      cur_img (i,j) = couleur;
    for (; j < y + tour*pas+1;j++)
      cur_img (i,j) = couleur;
    for (; i > x - tour*pas-1 ;i--)
      cur_img (i,j) = couleur;
    for (; j > y - tour*pas-1;j--)
      cur_img (i,j) = couleur;
  }
}

void spiral_regular (int xdebut, int xfin, int ydebut, int yfin, int pas, int nbtours)
{
  int i,j;
  int taille = nbtours * pas + 2;
  
  for (i = xdebut + taille; i < xfin - taille; i += 2*taille)
    for (j = ydebut + taille; j < yfin - taille; j += 2*taille)
      spiral (i,j, pas, nbtours); 
}
