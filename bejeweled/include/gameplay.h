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

/* *********************** try_swap **************************
   * bool try_swap(gameboard &gb, diamond &a, diamond &b,    *
   *               SDL_Surface *ps);                         *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 01 Decembre 2010, v0.4                 *
   ********************* Description *************************
   * Cette fonction permet de tenter l'echange de deux       *
   * diamants.                                               *
   *********************** Entrees ***************************
   * `gb' : reference sur le plateau ou effectuer l'echange  *
   * `a'  : diamant a echanger                               *
   * `b'  : diamant a echanger                               *
   * `ps' : pointeur sur la surface ou dessiner l'echange    *
   *        graphiquement                                    *
   *********************** Sorties ***************************
   * `bool' : true si l'echange a ete correctement effectue, *
   *          false sinon                                    *
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

/* *********************** get_down **************************
   * void get_down(gameboard &gb, SDL_Surface *ps);          *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 05 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Suite a une explosion, cette fonction est appelee pour  *
   * remplacer les diamants retires du jeu par ceux du       *
   * dessus (si aucun diamant ne se trouve dessus, de        *
   * nouveaux diamants sont ajoutes aleatoirement).          *
   *********************** Entrees ***************************
   * `gb' : plateau ou faire descendre les diamants          *
   * `ps' : surface ou dessiner la descente des diamants     *
   *        - - - - - - - - - - - - - - - - - - - - - - - -  *
   *        NOTE: gestion graphique non supportee pour       *
   *        l'instant                                        *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void get_down(gameboard &gb, SDL_Surface *ps);

/* ******************* check_hpattern_3x2 ********************
   * bool check_hpattern_3x2(gameboard &gb, int i, int j);   *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.6                 *
   ********************* Description *************************
   * Cette fonction permet de determiner si il existe au     *
   * moins une solution horizontale en se basant sur les     *
   * motifs 3*2. Voir la section "Motifs" plus bas dans le   *
   * code pour plus d'informations.                          *
   *********************** Entrees ***************************
   * `gb' : plateau ou chercher une solution                 *
   * `i'  : indice ligne debut motif                         *
   * `j'  : indice colonne debut motif                       *
   *********************** Sorties ***************************
   * `bool' : true si un motif est trouve, false sinon       *
   *********************************************************** */
bool check_hpattern_3x2(gameboard &gb, int i, int j);

/* ******************* check_vpattern_3x2 ********************
   * bool check_vpattern_3x2(gameboard &gb, int i, int j);   *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.6                 *
   ********************* Description *************************
   * Cette fonction permet de determiner si il existe au     *
   * moins une solution verticale en se basant sur les       *
   * motifs 3*2. Voir la section "Motifs" plus bas dans le   *
   * code pour plus d'informations.                          *
   *********************** Entrees ***************************
   * `gb' : plateau ou chercher une solution                 *
   * `i'  : indice ligne debut motif                         *
   * `j'  : indice colonne debut motif                       *
   *********************** Sorties ***************************
   * `bool' : true si un motif est trouve, false sinon       *
   *********************************************************** */
bool check_vpattern_3x2(gameboard &gb, int i, int j);

/* ******************* check_hpattern_4x1 ********************
   * bool check_hpattern_4x1(gameboard &gb, int i, int j);   *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.6                 *
   ********************* Description *************************
   * Cette fonction permet de determiner si il existe au     *
   * moins une solution horizontale en se basant sur les     *
   * motifs 4*1. Voir la section "Motifs" plus bas dans le   *
   * code pour plus d'informations.                          *
   *********************** Entrees ***************************
   * `gb' : plateau ou chercher une solution                 *
   * `i'  : indice ligne debut motif                         *
   * `j'  : indice colonne debut motif                       *
   *********************** Sorties ***************************
   * `bool' : true si un motif est trouve, false sinon       *
   *********************************************************** */
bool check_hpattern_4x1(gameboard &gb, int i, int j);

/* ******************* check_vpattern_4x1 ********************
   * bool check_vpattern_4x1(gameboard &gb, int i, int j);   *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 Decembre 2010, v0.6                 *
   ********************* Description *************************
   * Cette fonction permet de determiner si il existe au     *
   * moins une solution verticale en se basant sur les       *
   * motifs 4*1. Voir la section "Motifs" plus bas dans le   *
   * code pour plus d'informations.                          *
   *********************** Entrees ***************************
   * `gb' : plateau ou chercher une solution                 *
   * `i'  : indice ligne debut motif                         *
   * `j'  : indice colonne debut motif                       *
   *********************** Sorties ***************************
   * `bool' : true si un motif est trouve, false sinon       *
   *********************************************************** */
bool check_vpattern_4x1(gameboard &gb, int i, int j);


/* ========== MOTIFS =========

       i:0 1 2 3    0 1 2 3
    j	 
    :
    0    D X D      X D X      Motif 3x2 : 1 (1 et 2)
    1    X D X      D X D

    0    X X D      D D X      Motif 3x2 : 2 (1 et 2)
    1    D D X      X X D

    0    D X X      X D D      Motif 3x2 : 2 (3 et 4)
    1    X D D      D X X

    0    X D X X    X X D X    Motif 4x1 : 3 (1 et 2)

    -------------------------

    0    X D        D X        Motif 3x2 : 1 (1 et 2)
    1    D X        X D
    2    X D        D X

    0    D X        X D        Motif 3x2 : 2 (1 et 2)
    1    D X        X D
    2    X D        D X

    0    D X        X D        Motif 3x2 : 2 (3 et 4)
    1    X D        D X
    2    X D        D X

    0    X          X          Motif 4x1 : 3 (1 et 2)
    1    D          X
    2    X          D
    3    X          X

   ========== MOTIFS ========= */

/* ******************** check_solution ***********************
   * bool check_solution(gameboard &gb);                     *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 Decembre 2010, v0.3                 *
   ********************* Description *************************
   * Cette fonction permet de savoir si il existe encore une *
   * solution possible dans le jeu. Lorsque cette fonction   *
   * renvoit false, si le joueur ne possede pas de bonus     *
   * Reanimation, la partie se termine.                      *
   *********************** Entrees ***************************
   * `gb' : plateau a verifier                               *
   *********************** Sorties ***************************
   * `bool' : true si un motif est trouve, false sinon       *
   *********************************************************** */
bool check_solution(gameboard &gb);

/* *********************** solo_loop *************************
   * bool main_loop(SDL_Surface *ps);                        *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 27 Novembre 2010, v1.3                 *
   ********************* Description *************************
   * Cette fonction est la boucle de jeu principale du mode  *
   * solo.                                                   *
   *********************** Entrees ***************************
   * `ps' : pointeur sur la surface de jeu                   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void solo_loop(SDL_Surface *ps);

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

#endif // guard
