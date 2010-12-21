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
    int col;               // nombre de colonnes dans la matrice
    int row;               // nombre de lignes dans la matrice
    diamond_matrix dmds;   // matrice de diamants
    diamond_indices expl;  // tableau d'indices explosions
    int nb_expl;           // nombre d'explosion qui doivent etre traitees
    int index_sol;         // indice d'une solution
    SDL_Surface *pieces;   // les 8 diamants
    SDL_Surface *grid;     // la grille
    SDL_Rect grid_rect;    // dimension de la grille et ou la placer à l'écran
    SDL_Surface *title_wp; // fond d'ecran titre
    SDL_Surface *game_wp;  // fond d'ecran jeu
    SDL_Surface *explode;  // les phases d'explosion
};

/* ******************** init_gameboard ***********************
   * void init_gameboard(gameboard &gb, int col, int row);   *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 20 Décembre 2010, v0.5                 *
   ********************* Description *************************
   * Cette fonction permet d'initialiser un plateau de jeu,  *
   * c'est a dire creer la matrice de diamant, charger les   *
   * images utilises par le plateau, et initialiser le       *
   * selecteur de diamant a 0.                               *
   *********************** Entrees ***************************
   * `gb'  : reference sur le plateau a initialiser          *
   * `col' : nombre de colonnes de la matrice à initialiser  *
   * `row' : nombre de lignes de la matrice à initialiser    *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void init_gameboard(gameboard &gb, int col, int row);

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

#endif // guard
