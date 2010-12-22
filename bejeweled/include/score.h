/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Projet AP1S1 2 : Bejeweled. A bejeweled-like game written in C++ with 
    the SDL, SDL_image and SDL_ttf libraries.

    Copyright (C) 2010  Dimitri Sabadie <dimitri.sabadie@etu.u-bordeaux1.fr>
    and                 Ludwig Raepsaet <ludwig.raepsaet@etu.u-bordeaux1.fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef SCORE_H
#define SCORE_H
#include "graphics.h"


void scores(TTF_Font *f, SDL_Surface *ps, int score);

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


#endif // guard
