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

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gameboard.h"
#include "graphics.h"

int const GRID_WIDTH   = 480;
int const GRID_HEIGHT  = 480;

/* ********************* check_explode ***********************
   * void check_explode(gameboard &gb);                      *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 novembre 2010, v0.3                 *
   ********************* Description *************************
   * Cette fonction parcourt la matrice de diamants et       *
   * marque les diamants a faire exploser.                   *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau ou chercher les         *
   *        diamants pouvant generer une explosion           *
   *********************** Sorties ***************************
   * `bool' : si aucun diamant n'a ete marque, cette         *
   *          fonction retourne false, sinon true            *
   *********************************************************** */
bool try_swap(gameboard &gb, diamond &a, diamond &b, SDL_Surface *ps);

/* ********************* check_explode ***********************
   * void check_explode(gameboard &gb);                      *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 novembre 2010, v0.3                 *
   ********************* Description *************************
   * Cette fonction parcourt la matrice de diamants et       *
   * marque les diamants a faire exploser.                   *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau ou chercher les         *
   *        diamants pouvant generer une explosion           *
   *********************** Sorties ***************************
   * `bool' : si aucun diamant n'a ete marque, cette         *
   *          fonction retourne false, sinon true            *
   *********************************************************** */
bool check_explode(gameboard &gb);

void explode(gameboard &gb, SDL_Surface *ps);

void get_down(gameboard &gb, SDL_Surface *ps);


bool check_hpattern_3x2(gameboard &gb, int i, int j);

bool check_vpattern_3x2(gameboard &gb, int i, int j);

bool check_hpattern_4x1(gameboard &gb, int i, int j);

bool check_vpattern_4x1(gameboard &gb, int i, int j);

/*
       i:0 1 2 3    0 1 2 3
    j	 
    :
    0    D X D      X D X
    1    X D X      D X D

    0    X X D      D D X
    1    D D X      X X D

    0    D X X      X D D
    1    X D D      D X X

    0    X D X X    X X D X

    -------------------------

    0    X D        D X
    1    D X        X D
    2    X D        D X

    0    D X        X D
    1    D X        X D
    2    X D        D X

    0    D X        X D
    1    X D        D X
    2    X D        D X

    0    X          X
    1    D          X
    2    X          D
    3    X          X


    16 combinaisons possibles
*/

bool check_solution(gameboard &gb);

// Fonction qui contient la boule de jeu principale
bool main_loop(SDL_Surface *ps);

bool cursor_in_grid(SDL_Event m, gameboard const &gb);

#endif // guard
