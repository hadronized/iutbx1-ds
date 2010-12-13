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
n
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SDL/SDL.h>
#include "matrix.h"

/* *********************** gameboard *************************
   * Dimitri Sabadie, 25 novembre 2010, v0.3                 *
   ********************** Description ************************
   * Cette structure represente le plateau de jeu.           *
   * `matrix' : represente la grille de diamants.            *
   * `pSel' : un pointeur sur diamond qui permet de savoir   *
   *        quel diamant le joueur est en train de           *
   *        selectionner. Dans le cas ou aucun diamant n'est *
   *        selectionne, le pointeur est a 0.                *
   * `imgs' : represente toutes les images utilisees par le  *
   *        plateau.                                         *
   *********************************************************** */
struct gameboard {
    diamond_matrix dmds;
    diamond_indices expl;
    int nb_expl;
    int index_sol;
    SDL_Surface *pieces;   // les 8 diamants
    SDL_Surface *grid;     // la grille
    SDL_Surface *title_wp; // fond d'ecran titre
    SDL_Surface *game_wp;  // fond d'ecran jeu
    SDL_Surface *explode;  // les phases d'explosion
};

/* ******************** init_gameboard ***********************
   * void init_gameboard(gameboard &gb);                     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 20 novembre 2010, v0.4                 *
   ********************* Description *************************
   * Cette fonction permet d'initialiser un plateau de jeu,  *
   * c'est a dire creer la matrice de diamant, charger les   *
   * images utilises par le plateau, et initialiser le       *
   * selecteur de diamant a 0.                               *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau a initialiser           *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void init_gameboard(gameboard &gb);

/* ********************* query_diamond ***********************
   * diamond query_diamond(gameboard &gb, int x, int y);     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 28 novembre 2010, v0.2                 *
   ********************* Description *************************
   * Cette fonction permet d'interroger la matrice de        *
   * diamants contenue dans le plateau de jeu passe en       *
   * parametre afin d'y chercher un diamant en se basant sur *
   * sa position (passee en parametre)                       *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau ou chercher le diamant  *
   * `x'  : colonne du diamant                               *
   * `y'  : ligne du diamant                                 *
   *********************** Sorties ***************************
   * diamond : le diamant demande                            *
   *********************************************************** */
diamond & query_diamond(gameboard &gb, int x, int y);

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

bool try_swap(gameboard &gb, diamond &a, diamond &b, SDL_Surface *ps);

void show_gameboard(gameboard &gb, SDL_Surface *ps);

void explode(gameboard &gb, SDL_Surface *ps);

void get_down(gameboard &gb, SDL_Surface *ps);

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

#endif // guard
