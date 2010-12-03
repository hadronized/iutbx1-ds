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

#ifndef ARRAY_H
#define ARRAY_H

/* ********************* array_insert ************************
   * bool array_insert(int x, int *a, int &n, int nmax);     *
   ********************* Auteur , Dates **********************
   * Dimitri Sabadie, 17 novembre 2010, v0.1                 *
   ********************** Description ************************
   * Cette fonction permet d'inserer un entier dans un       *
   * tableau d'entiers. Si l'entier est deja present dans le *
   * tableau, le doublon n'est alors pas insere.             *
   ************************ Entrees **************************
   * `x' : l'entier a ajouter                                *
   * `a' : le tableau ou ajouter l'entier                    *
   * `n' : la taille « pseudo dynamique » actuelle du        *
   *       tableau                                           *
   * `nmax' : la taille maximale du tableau                  *
   ************************ Sorties **************************
   * `bool' : true si l'insertion s'est bien deroulee, false *
   *          sinon                                          *
   *********************************************************** */
bool array_insert(int x, int *a, int &n, int nmax);

/* *********************** array_find ************************
   * bool array_find(int *x, int *a, int n);                 *
   ********************* Auteur , Dates **********************
   * Dimitri Sabadie, 20 novembre 2010, v0.1                 *
   ********************** Description ************************
   * Cette fonction permet de rechercher dans un tableau     *
   * d'entiers non trie un entier.                           *
   ************************ Entrees **************************
   * `x' : l'entier a rechercher                             *
   * `a' : le tableau ou rechercher l'entier                 *
   * `n' : la taille « pseudo dynamique » actuelle du        *
   *       tableau                                           *
   ************************ Sorties **************************
   * `bool' : true si l'entier a ete trouve, false sinon     *
   *********************************************************** */
bool array_find(int x, int *a, int n);

// Uniquement pour tests. Affiche un tableau dans la console.
void show_array(int *a, int n);


#endif // guard
