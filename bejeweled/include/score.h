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

#include <string>
#include "graphics.h"

using namespace std;

string const TOP_TEN_SOLO_FILE = ".sbt10f"; // Solo Bejeweled Top 10 file
string const TOP_TEN_COOP_FILE = ".cbt10f"; // Cooperation Bejeweled Top 10 file

// Fonction Ludwig
void scores(TTF_Font *f, SDL_Surface *ps, int x, int score);

/* *********************** free_font *************************
   * void free_font(TTF_Font *pf);                           *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction libere une police deja initialisee       *
   *********************** Entrees ***************************
   * `pf'  : pointeur sur la police precedement initialisée  *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void free_font(TTF_Font *pf);

/* *********************** init_font()   *********************
   * TTF_Font * init_font();                                 *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet d'initialiser une police          *
   *********************** Entrees ***************************
   *                                                         *
   *********************** Sorties ***************************
   * `pf' : retourne la police initialisee                   *
   *********************************************************** */
TTF_Font * init_font();

/* ************************ is_alphanum **********************
   * bool is_alphanum(Uint16 unicode);                       *
   *********************** Auteur , Dates ********************
   * Dimitri Sabadie, 25 Decembre 2010, v0.1                 *
   *********************** Description ***********************
   * Cette fonction permet de determiner si un caractere     *
   * donne est alphanumerique (A-Za-z0-9).                   *
   *********************** Entrees ***************************
   * `unicode' : le caractere a teste                        *
   *********************** Sorties ***************************
   * `bool' : true si le caractere est alphanumerique, false *
   *          sinon                                          *
   *********************************************************** */
bool is_alphanum(Uint16 unicode);

/* *********************** get_username **********************
   * string get_username(int place, TTF_Font *pf,            *
   *                     SDL_Surface *ps);                   *
   *********************** Auteur , Dates ********************
   * Dimitri Sabadie, 27 Decembre 2010, v0.2                 *
   *********************** Description ***********************
   * Cette fonction permet de recuperer le nom d'utilisateur *
   * d'un joueur sous forme de 3 caracteres.                 *
   *********************** Entrees ***************************
   * `place' : position du joueur dans le classement         *
   * `pf'    : pointeur sur la police a utiliser pour la     *
   *           saisie                                        *
   * `ps'    : pointeur sur la surface ou afficher la saisie *
   *********************** Sorties ***************************
   * `string' : le nom d'utilisateur entre                   *
   *********************************************************** */
string get_username(int place, TTF_Font *pf, SDL_Surface *ps);

/* *********************** in_top_ten_solo *******************
   * void in_top_ten_solo(TTF_Font *pf, SDL_Surface *ps,     *
   *                      int score);                        *
   *********************** Auteur , Dates ********************
   * Dimitri Sabadie, 23 Decembre 2010, v0.1                 *
   *********************** Description ***********************
   * Cette fonction permet de savoir si un joueur a battu    *
   * un record et rentre donc dans le Top 10 en mode Solo.   *
   * Si tel est le cas, il est invite a rentrer son pseudo.  *
   *********************** Entrees ***************************
   * `pf' : pointeur sur la police a utiliser pour la saisie *
   * `ps' : pointeur sur la surface ou afficher la saisie    *
   * `score' : score du joueur                               *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void in_top_ten_solo(TTF_Font *pf, SDL_Surface *ps, int score);

#endif // guard
