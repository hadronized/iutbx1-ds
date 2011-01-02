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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "diamond.h"
#include "gameboard.h"

/* *********************** keyboard **************************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Cette structure represente un clavier. Elle est         *
   * utilisee pour ajouter un deuxieme joueur dans le jeu.   *
   * Le champs `hover' represente simplement le diamant      *
   *survole, et le champs `lock' represente le diamant       *
   * selectionne.                                            *
   *********************************************************** */
struct keyboard {
    int hover;    // indice du diamant survole
    int lock;     // indice du diamant selectionne
    int col;  // nombre de colonnes dans la matrice de diamants
    int row;  // nombre de lignes dans la matrice de diamants
};

/* ********************* init_keyboard ***********************
   * void init_keyboard(keyboard &kb, gameboard const &gb);  *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Initialise un claver.                                   *
   *********************** Entrees ***************************
   * `kb' : clavier a initialiser                            *
   * `gb' : plateau de jeu dans lequel sera utilise le       *
   *        clavier                                          *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void init_keyboard(keyboard &kb, gameboard const &gb);

/* ******************* keyboard_update_up ********************
   * void keyboard_update_up(keyboard &gb);                  *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Permet de faire monter le curseur de diamant.           *
   *********************** Entrees ***************************
   * `kb' : clavier contenant le curseur                     *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void keyboard_update_up(keyboard &gb);

/* ****************** keyboard_update_down *******************
   * void keyboard_update_down(keyboard &gb);                *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Permet de faire descendre le curseur de diamant.        *
   *********************** Entrees ***************************
   * `kb' : clavier contenant le curseur                     *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void keyboard_update_down(keyboard &gb);

/* ****************** keyboard_update_left *******************
   * void keyboard_update_left(keyboard &gb);                *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Permet de decaler a gauche le curseur de diamant.       *
   *********************** Entrees ***************************
   * `kb' : clavier contenant le curseur                     *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void keyboard_update_left(keyboard &gb);

/* ***************** keyboard_update_right *******************
   * void keyboard_update_right(keyboard &gb);               *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Permet de decaler a droite le curseur de diamant.       *
   *********************** Entrees ***************************
   * `kb' : clavier contenant le curseur                     *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void keyboard_update_right(keyboard &gb);

/* ********************* keyboard_lock ***********************
   * void keyboard_lock(keyboard &kb, bool lock);            *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Janvier 2011, v0.1                  *
   ********************* Description *************************
   * Selectionne ou deselectionne un diamant.                *
   *********************** Entrees ***************************
   * `kb'   : clavier contenant le curseur                   *
   * `lock' : determine si on doit selectionner ou non       *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void keyboard_lock(keyboard &kb, bool lock);

#endif // guard
