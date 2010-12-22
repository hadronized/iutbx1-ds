#include "graphics.h"
#include <time.h>

void affiche_temps(TTF_Font *f, SDL_Surface *ps, int temps_restant);

/* *********************** affiche_temps *********************
   * void affiche_temps(TTF_Font *f, SDL_Surface *ps);       *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet d'afficher le temps               *
   *********************** Entrees ***************************
   * `ps' : pointeur sur la surface                          * 
   * `f'  : pointeur sur la police                           *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
