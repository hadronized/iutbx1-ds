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

#ifndef CIPHER_H
#define CIPHER_H

#include <string>

using namespace std;

string const XOR_KEY = "This is a really funny key used to crypt and \
decrypt data. PLEASE DO NOT MODIFY IT !";

/* ************************ crypt ****************************
   * string crypt(std::string const &data);                  *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 12 Decembre 2010, v0.3                 *
   ******************** Description **************************
   * Cette fonction permet de crypter une chaine de          *
   * caracteres en utilisant l'associativite du OU EXCLUSIF. *
   ********************** Entrees ****************************
   * `data' : chaine en entree, claire                       *
   ********************** Sorties ****************************
   * `string' : chaine en sortie, cryptee                    *
   *********************************************************** */
string crypt(std::string const &data);

/* ********************** decrypt ****************************
   * string decrypt(std::string const &data);                *
   ******************* Auteur , Dates ************************
   * Dimitri Sabadie, 12 Decembre 2010, v0.3                 *
   ******************** Description **************************
   * Cette fonction permet de decrypter une chaine de        *
   * caracteres en utilisant l'associativite du OU EXCLUSIF. *
   ********************** Entrees ****************************
   * `data' : chaine en entree, cryptee                      *
   ********************** Sorties ****************************
   * `string' : chaine en sortie, claire                     *
   *********************************************************** */
string decrypt(std::string const &data);

#endif // guard
