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

#ifndef DIAMOND_H
#define DIAMOND_H

#include <SDL/SDL.h>

typedef int diamond_type;

int const DIAMOND_TYPE_N = 8;
int const DIAMOND_SIZE   = 60;
int const DIAMOND_SPEED  = 4;

/* *********************** diamond ***************************
   * Dimitri Sabadie, 9 novembre 2010, v0.2                  *
   ********************* Description *************************
   * Cette structure represente un diamant. Il est important *
   * de noter qu'elle ne contient pas d'image, juste le      *
   * type de diamant, pour eviter d'avoir des ambiguites     *
   *********************************************************** */
struct diamond {
    diamond_type type;  // type du diamant
    int x;              // position x dans la matrice du diamant
    int y;              // position y dans la matrice du diamant
    SDL_Rect box;
    SDL_Rect sub;
};

/* ******************** init_diamond *************************
   * diamond_type init_diamond(diamond&, int x, int y,       *
   *                           int kind);                    *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 30 Decembre 2010, v0.3                 *
   ******************** Description **************************
   * Cette fonction permet d'initialiser un diamant, a       *
   * savoir, lui attribuer un type au hasard, ainsi qu'une   *
   * position donnee dans la matrice.                        *
   ********************** Entrees ****************************
   * `d'    : reference sur le diamant a initialiser         *
   * `x'    : entier representant l'abscisse du diamant a    *
   *          initialiser                                    *
   * `y'    : entier representant l'ordonnee du diamant e    *
   *          initialiser                                    *
   * `kind' : nombre de types de diamants                    *
   ********************** Sorties ****************************
   * `diamond_type' : type de diamant genere                 *
   *********************************************************** */
diamond_type init_diamond(diamond &d, int x, int y, int kind);

/* ***************** change_diamond_type *********************
   * void change_diamond_type(diamond &d, diamond_type h,    *
   *                          diamond_type v, int kind);     *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 30 Decembre 2010, v0.2                 *
   ******************** Description **************************
   * Cette fonction permet de changer le type d'un diamant   *
   * en prenant en compte deux autres types de diamant.      *
   * Cette fonction est utilisee pour generer une matrice de *
   * diamants qui ne contient pas de diamants alignes.       *
   ********************** Entrees ****************************
   * `d'    : reference sur le diamant contenant le type     *
   * `h'    : diamant horizontal (a droite)                  *
   * `v'    : diamant vertical (au dessus)                   *
   * `kind' : nombre de types de diamants                    *
   ********************** Sorties ****************************
   * void                                                    *
   *********************************************************** */
void change_diamond_type(diamond &d, diamond_type h, diamond_type v, int kind);

/* *********************** is_near ***************************
   * bool is_near(diamond const &a, diamond const &b);       *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 12 novembre 2010, v0.1                 *  
   ********************* Description *************************
   * Cette fonction permet de verifier que deux diamants     *
   * peuvent bien etre echanges. Attention, cette fonction   *
   * n'assure pas qu'une explosion va se produire, elle      *
   * assure uniquement que les deux diamants passes en       *
   * parametres sont suffisament proches pour pouvoir etre   *
   * echanges.                                               *
   *********************** Entrees ***************************
   * `a' : un diamant selectionne                            *
   * `b' : un autre diamant selectionne                      *
   ********************** Sorties ****************************
   * `bool' : vrai si les diamants sont suffisament pres     *
   *          pour tenter un echange                         *
   *********************************************************** */
bool is_near(diamond const &a, diamond const &b);

/* *********************** is_near ***************************
   * void diamond_swap(diamond &a, diamond &b);              *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 novembre 2010, v0.1                 *  
   ********************* Description *************************
   * Echange le type de deux diamants. Attention, les        *
   * coordonnees des diamants ne sont pas echangees.         *
   *********************** Entrees ***************************
   * `a' : un diamant selectionne                            *
   * `b' : un autre diamant selectionne                      *
   ********************** Sorties ****************************
   * void                                                    *
   *********************************************************** */
void diamond_swap(diamond &a, diamond &b);

/* ************************* equal ***************************
   * bool equal(diamond a, diamond b, diamond c);            *
   ******************** Auteur , Dates ***********************
   * Dimitri Sabadie, 21 novembre 2010, v0.1                 *  
   ********************* Description *************************
   * Permet de verifier que 3 diamants ont le meme type.     *
   *********************** Entrees ***************************
   * `a' : un diamant                                        *
   * `b' : un autre diamant                                  *
   * `c' : et encore un autre                                *
   ********************** Sorties ****************************
   * `bool' : true si les diamants ont tous le meme type,    *
   *          false sinon                                    *
   *********************************************************** */
bool equal(diamond a, diamond b, diamond c);

#endif // guard
