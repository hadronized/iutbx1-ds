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

#include <iostream>
#include <fstream>
#include <sstream>
#include "cipher.h"
#include "game_save.h"

using namespace std;

void save_solo_game(gameboard const &gb, int score) {
    ofstream file;
    stringstream data;

    file.open(SOLO_SAVE_FILE.c_str(), ios::trunc);

    if (file.is_open()) {
        data << gb.col << endl;
        data << gb.row << endl;
        for (int i = 0; i < MATRIX_HEIGHT*MATRIX_WIDTH; ++i)
            data << gb.dmds[i].type << ' ';
        // écrire le temps restant ici
        data << endl;
        data << score << endl;

        file << crypt(data.str());
        file.close();
    } else {
        cerr << '[' << SOLO_SAVE_FILE << "] : fichier non accessible pour sauvegarde" << endl;
    }
}

void load_solo_game(gameboard &gb, int &score) {
    ifstream file;
    stringstream cdata;
    stringstream ddata;
    diamond *pd;

    file.open(SOLO_SAVE_FILE.c_str());

    if (file.is_open()) {
        cdata << file.rdbuf();
        file.close();
        
        ddata << decrypt(cdata.str());
        ddata >> gb.col >> gb.row;
        gb.dmds = new diamond[gb.col*gb.row];
        for (int j = 0; j < gb.col; ++j) {
            for (int i = 0; i < gb.row; ++i) {
                pd = &query_diamond(gb, i, j),
                init_diamond(*pd, i, j);
                ddata >> pd->type;
                pd->sub.x = pd->type*DIAMOND_SIZE;
            }
        }
            
        ddata >> score;
    } else {
        cerr << '[' << SOLO_SAVE_FILE << "] : fichier non accessible pour chargement" << endl;
    }
}

