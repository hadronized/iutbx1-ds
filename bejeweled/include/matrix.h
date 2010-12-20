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

#ifndef MATRIX_H
#define MATRIX_H

#include "diamond.h"

int const MATRIX_WIDTH   = 8;
int const MATRIX_HEIGHT  = 8;
int const MATRIX_DIMENSION = MATRIX_WIDTH*MATRIX_HEIGHT;

typedef diamond *diamond_matrix;
typedef int *diamond_indices;

/* ************************ index_2D1D ***********************
   * int index_2D1D(int i, int j, int w);                    *
   ********************* Auteur , Dates **********************
   * Dimitri Sabadie, 20 Decembre 2010, v0.2                 *
   ********************** Description ************************
   * Cette fonction permet de transformer un couple          *
   * d'indices (i;j) referencant une case d'une matrice en   *
   * un unique indice referencant la meme case de la matrice *
   * ramene a une seule dimension.                           *
   ************************ Entrees **************************
   * `i' : indice de la colonne                              *
   * `j' : indice de la ligne                                *
   * `w' : longueur de la matrice ou transformer les indices *
   ************************ Sorties **************************
   * int : indice transforme du couple(i;j)                  *
   *********************************************************** */
int index_2D1D(int i, int j, int w);

/* ************************ index_1D2D ***********************
   * int index_1D2D(int i, int j, int w);                    *
   ********************* Auteur , Dates **********************
   * Dimitri Sabadie, 20 Decemebre 2010, v0.2                *
   ********************** Description ************************
   * Cette fonction permet de transformer un indice          *
   * referencant une case d'une matricve en un couple        *
   * d'indices donnant la position de la case en considerant *
   * le tableau comme bidimensionnel.                        *
   ************************ Entrees **************************
   * `x' : indice à transformer                              *
   * `i' : reference sur l'indice de la colonne              *
   * `j' : reference sur l'indice de la ligne                *
   * `w' : longueur de la matrice ou transformer les indices *
   ************************ Sorties **************************
   * void                                                    *
   *********************************************************** */
void index_1D2D(int x, int &i, int &j, int w);

#endif // guard
