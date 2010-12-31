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

#ifndef GAME_SAVE_H
#define GAME_SAVE_H

#include <string>
#include "gameboard.h"

std::string const SOLO_SAVE_FILE = ".last.sbsvf"; // Solo Bejeweled Save file

/* ******************** save_solo_game ***********************
   * void save_solo_game(gameboard const &gb, int score);    *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 11 Decembre 2010, v0.3                 *
   ********************* Description *************************
   * Cette fonction permet de sauvegarder la progression     *
   * d'un joueur en mode Solo.                               *
   *********************** Entrees ***************************
   * `gb'    : reference sur le plateau a sauvegarder        *
   * `score' : score du joueur                               *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */

/* ******************** load_solo_game ***********************
   * void load_solo_game(gameboard &gb, int &score);         *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 11 Decembre 2010, v0.3                 *
   ********************* Description *************************
   * Cette fonction permet de recuperer la progression d'un  *
   * joueur en mode Solo.                                    *
   *********************** Entrees ***************************
   * `gb'    : reference sur le plateau a recuperer          *
   * `score' : score du joueur                               *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void save_solo_game(gameboard const &gb, int score);
void load_solo_game(gameboard &gb, int &score);

#endif // guard
