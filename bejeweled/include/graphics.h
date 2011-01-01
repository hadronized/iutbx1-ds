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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "gameplay.h"
#include "game_param.h"

using namespace std;

int const  SCREEN_WIDTH   = 720;
int const  SCREEN_HEIGHT  = 480;
int const  SCREEN_DEPTH   = 32;
string const SCREEN_TITLE = "Bejeweled !";

/* *********************** init_gui **************************
   * bool init_gui(void);                                    *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 9  Novembre 2010, v0.1                 *
   ********************* Description *************************
   * Permet d'initialiser l'interface graphique (SDL,        *
   * SDL_image, SDL_ttf).                                    *
   *********************** Entrees ***************************
   * void                                                    *
   *********************** Sorties ***************************
   * `bool' : true si tout s'est bien passe, false sinon     *
   *********************************************************** */
bool init_gui(void);

/* *********************** quit_gui **************************
   * void quit_gui(void);                                    *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 9  Novembre 2010, v0.1                 *
   ********************* Description *************************
   * Permet de liberer les ressources prises par les         *
   * bibliotheque GUI.                                       *
   *********************** Entrees ***************************
   * void                                                    *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void quit_gui(void);

/* ********************* create_screen ***********************
   * SDL_Surface * create_screen(void);                      *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 9 Novembre 2010, v0.1                  *
   ********************* Description *************************
   * Permet de recuperer la surface elementaire de dessins ( *
   * l'ecran). Attention, cette surface doit etre liberee    *
   * par SDL_FreeSurface(SDL_Surface *).                    *
   *********************** Entrees ***************************
   * void                                                    *
   *********************** Sorties ***************************
   * `SDL_Surface*' : pointeur sur la surface representant   *
   *                  l'ecran                                *
   *********************************************************** */
SDL_Surface * create_screen(void);

/* ********************** load_theme *************************
   * bool load_theme(string const &name, gameboard &gb);     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 28 Novembre 2010, v0.1                 *
   ********************* Description *************************
   * Permet de changer le theme graphique utilise dans le    *
   * Plusieurs elements composent un theme :                 *
   *   · image diamants                                      *
   *   · image fond de jeu                                   *
   *   · image fond de titre                                 *
   *   · image explosions                                    *
   *   · image grille                                        *
   *********************** Entrees ***************************
   * `name' : nom du repertoire du theme, qui doit se        *
   *          terminer par un '/'                            *
   * `gb'   : plateau auquel affecter le theme               *
   *********************** Sorties ***************************
   * `bool' : true si le theme a bien ete charge, false      *
   *          sinon                                          *
   *********************************************************** */
bool load_theme(string const &name, gameboard &gb);

/* ********************** free_theme *************************
   * void free_theme(gameboard &gb);                         *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 28 Novembre 2010, v0.1                 *
   ********************* Description *************************
   * Libere les ressources prises par un theme.              *
   *********************** Entrees ***************************
   * `gb' : plateau contenant le theme                       *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void free_theme(gameboard &gb);

/* ******************** cursor_in_grid ***********************
   * bool cursor_in_grid(SDL_Event m, gameboard const &gb);  *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 Decembre 2010, v0.2                 *
   ********************* Description *************************
   * Cette fonction permet de savoir si le curseur de la     *
   * souris se situe bien dans une grille jouable.           *
   *********************** Entrees ***************************
   * `m'  : evenement par laquelle l'etat de la souris peut  *
   *        etre recupere                                    *
   * `gb' : reference sur le plateau contenant la grille     *
   *********************** Sorties ***************************
   * `bool' : true si le curseur est dans la grille, false   *
   *          sinon                                          *
   *********************************************************** */
bool cursor_in_grid(SDL_Event m, gameboard const &gb);

/* ******************** show_gameboard ***********************
   * void show_gameboard(gameboard &gb, SDL_Surface *ps);    *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 Decembre 2010, v0.4                 *
   ********************* Description *************************
   * Cette fonction permet d'afficher un plateau a l'ecran,  *
   * c'est a dire le fond de jeu, la grille et tous les      *
   * diamants.                                               *
   *********************** Entrees ***************************
   * `gb' : plateau a afficher                               *
   * `ps' : pointeur sur la surface ou dessiner le plateau   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void show_gameboard(gameboard &gb, SDL_Surface *ps);

/* ********************* draw_game_wp ************************
   * void draw_game_wp(gameboard &gb, SDL_Rect *sub,         *
   *                   SDL_Surface *ps);                     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Affiche le fond de jeu.                                 *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant le fond de jeu a afficher     *
   * `sub' : non utilise                                     *
   * `ps'  : pointeur sur la surface ou dessiner le fond de  *
   *         jeu                                             *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_game_wp(gameboard &gb, SDL_Rect *sub, SDL_Surface *ps);

/* *********************** draw_grid *************************
   * void draw_grid(gameboard &gb, SDL_Surface *ps);         *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Affiche la grille                                       *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant la grille a afficher          *
   * `ps'  : pointeur sur la surface ou dessiner la grille   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_grid(gameboard &gb, SDL_Surface *ps);

/* ********************* draw_diamond ************************
   * void draw_diamond(gameboard &gb, diamond &d,            *
   *                   SDL_Surface *ps);                     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Affiche un diamant.                                     *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant le diamant a afficher         *
   * `d'   : diamant a afficher                              *
   * `ps'  : pointeur sur la surface ou dessiner le diamant  *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_diamond(gameboard &gb, diamond &d, SDL_Surface *ps);

/* ************************ explode **************************
   * void explode(gameboard &gb, SDL_Surface *ps);           *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Decembre 2010, v0.2                 *
   ********************* Description *************************
   * Cette fonction permet de retirer du plateau les         *
   * diamants alignes en les faisant exploser.               *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau ou retirer les          *
   *        explosions                                       *
   * `ps' : pointeur sur la surface ou dessiner les          *
   *        explosions graphiquement                         *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void explode(gameboard &gb, SDL_Surface *ps);

/* ***************** * draw_diamond_swap *********************
   * void draw_diamond_swap(gameboard &gb, diamond &a,       *
   *                        diamond &b, int vx, int vy,      *
   *                        SDL_Surface *ps);                *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 14 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Echange graphiquement deux diamants.                    *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant les deux diamants a echanger  *
   * `a'   : premier diamant                                 *
   * `b'   : deuxieme diamant                                *
   * `vx'  : abscisse du vecteur d'echange                   *
   * `vy'  : ordonnee du vecteur d'echange                   *
   * `ps'  : pointeur sur la surface ou dessiner l'echange   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_diamond_swap(gameboard &gb, diamond &a, diamond &b, int vx, int vy, SDL_Surface *ps);

/* ********************* draw_getdown ************************
   * void draw_getdown(gameboard &gb, SDL_Surface *ps);      *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, ?? Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Fait descendre graphiquement des diamants.              *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant les diamants a faire          *
   *         descendre                                       *
   * `ps'  : pointeur sur la surface ou dessiner la descente *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_getdown(gameboard &gb, SDL_Surface *ps); // a compléter ! :)

/* ******************** draw_solution ************************
   * A COMPLETER
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 22 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Attire l'attention du joueur sur un diamant en          *
   * particulier dans le but de lui indiquer qu'il s'agit    *
   * d'une solution.                                         *
   *********************** Entrees ***************************
   * `gb'  : plateau contenant une solution                  *
   * `ps'  : pointeur sur la surface ou dessiner la solution *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_solution(gameboard &gb, SDL_Surface *ps);

/* *********************** game_over *************************
   * void game_over(gameboard &gb, TTF_Font *pf,             *
   *                SDL_Surface *ps);                        *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 Decembre 2010, v0.2                 *
   ********************* Description *************************
   * Cette fonction permet d'afficher l'animation de         *
   * game over.                                              *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau de jeu fini             *
   * `pf' : pointeur sur la police a utiliser                *
   * `ps' : pointeur sur la surface a utiliser               *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void game_over(gameboard &gb, TTF_Font *pf, SDL_Surface *ps);

/* ********************* draw_top_ten ************************
   * void draw_top_ten(TTF_Font *pf, SDL_Surface *ps);       *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 28 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Cette fonction permet d'afficher les 10 meilleurs       *
   * scores du mode Solo.                                    *
   *********************** Entrees ***************************
   * `pf' : pointeur sur la police a utiliser                *
   * `ps' : pointeur sur la surfouce ou afficher le top 10   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void draw_top_ten(TTF_Font *pf, SDL_Surface *ps);

#endif // guard
