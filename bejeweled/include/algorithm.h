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

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <SDL/SDL.h>
/* ********************** int_swap ***************************
   * diamond_type init_diamond(diamond&, int x, int y);      *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 21 novembre 2010, v0.1                 *
   ******************** Description **************************
   * Cette fonction permet d'echanger deux entiers.          *
   ********************** Entrees ****************************
   * `a' : reference sur le premier entier                   *
   * `b' : reference sur le deuxieme entier                  *
   ********************** Sorties ****************************
   * void                                                    *
   *********************************************************** */
void int_swap(int &a, int &b);

void sdlrect_swap(SDL_Rect &a, SDL_Rect &b);

#endif // guard
