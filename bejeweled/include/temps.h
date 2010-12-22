#include "graphics.h"
#include <time.h>

void affiche_temps(TTF_Font *f, SDL_Surface *ps);

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
void free_font(TTF_Font *pf);

/* *********************** free_font *************************
   * void free_font(TTF_Font *pf);                           *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction libere une police deja initialisée      *
   *********************** Entrees ***************************
   * `pf'  : pointeur sur la police precedement initialisée  *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */

TTF_Font * init_font();

/* *********************** init_font()   *********************
   * TTF_Font * init_font();                                *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction d'initialiser une police                 *
   *********************** Entrees ***************************
   *                                                         *
   *********************** Sorties ***************************
   * `pf' : retourne la police initialisée                   *
   *********************************************************** */
