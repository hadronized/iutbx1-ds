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

#ifndef GAME_PARAM_H
#define GAME_PARAM_H

/* ********************** game_param *************************
   * Dimitri Sabadie, 29 Decembre 2010, v0.1                 *
   ********************* Description *************************
   * Cette structure permet de parametrer un jeu en fonction *
   * de la difficulte choisie par le joueur.                 *
   *********************************************************** */
struct game_param {
    int nbKind;     // Disparite des diamants avec l'assertion : min=3, max=8
    int endMult;    // Multiplicateur de fin de partie
    int pPD;        // Points par diamant
    int time;       // Temps de départ
    int posTime;    // Temps positif : temps credite a chaque diamant explose
    int negTime;    // Temps negatif : temps debite a chaque mauvaise tentative
    int actPoints;  // Points necessaire depuis le debut du jeu ou dernier Action pour avoir un Action
    int reaPoints;  // Points necessaire depuis le debut du jeu ou derniere Reanimation pour avoir un Reanimation
};



/* ******************** init_diamond *************************
   * diamond_type init_diamond(diamond&, int x, int y);      *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 9 novembre 2010, v0.2                  *  
   ******************** Description **************************
   * Cette fonction permet d'initialiser un diamant, a       *
   * savoir, lui attribuer un type au hasard, ainsi qu'une   *
   * position donnee dans la matrice.                        *
   ********************** Entrees ****************************
   * `d' : reference sur le diamant a initialiser            *
   * `x' : entier representant l'abscisse du diamant a       *
   *       initialiser                                       *
   * `y' : entier representant l'ordonnee du diamant e       *
   *       initialiser                                       *
   ********************** Sorties ****************************
   * `diamond_type' : type de diamant genere                 *
   *********************************************************** */

#endif // guard
