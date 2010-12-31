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

#include <iostream> // pour cerr
#include <fstream>
#include "game_param.h"

game_param get_solo_param(difficulty diff) {
    game_param gp;

    switch (diff) {
        case easy :
            gp.nbKind = 6;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 90;
            gp.posTime = 10;
            gp.actPoints = 60;
            gp.reaPoints = 120;
            break;

        case normal :
            gp.nbKind = 7;
            gp.endMult = 2;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 5;
            gp.actPoints = 120;
            gp.reaPoints = 240;
            break;

        case heroic :
            gp.nbKind = 8;
            gp.endMult = 3;
            gp.pPD = 2;
            gp.time = 20;
            gp.posTime = 2;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        case legendary :
            gp.nbKind = 8;
            gp.endMult = 4;
            gp.pPD = 2;
            gp.time = 10;
            gp.posTime = 1;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        default :
            gp.nbKind = 7;
            gp.endMult = 2;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 5;
            gp.actPoints = 120;
            gp.reaPoints = 240;
    }
            
    return gp;
}

game_param get_dual_param(difficulty diff) {
    game_param gp;

    switch (diff) {
        case easy :
            gp.nbKind = 6;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 90;
            gp.posTime = 10;
            gp.actPoints = 60;
            gp.reaPoints = 120;
            break;

        case normal :
            gp.nbKind = 7;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 5;
            gp.actPoints = 120;
            gp.reaPoints = 240;
            break;

        case heroic :
            gp.nbKind = 8;
            gp.endMult = 1;
            gp.pPD = 2;
            gp.time = 20;
            gp.posTime = 2;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        case legendary :
            gp.nbKind = 8;
            gp.endMult = 1;
            gp.pPD = 2;
            gp.time = 10;
            gp.posTime = 1;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        default :
            gp.nbKind = 7;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 5;
            gp.actPoints = 120;
            gp.reaPoints = 240;
    }
            
    return gp;
}

game_param get_coop_param(difficulty diff) {
    game_param gp;

    switch (diff) {
        case easy :
            gp.nbKind = 7;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 10;
            gp.actPoints = 60;
            gp.reaPoints = 120;
            break;

        case normal :
            gp.nbKind = 8;
            gp.endMult = 2;
            gp.pPD = 1;
            gp.time = 30;
            gp.posTime = 10;
            gp.actPoints = 120;
            gp.reaPoints = 240;
            break;

        case heroic :
            gp.nbKind = 8;
            gp.endMult = 3;
            gp.pPD = 2;
            gp.time = 10;
            gp.posTime = 2;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        case legendary :
            gp.nbKind = 8;
            gp.endMult = 4;
            gp.pPD = 2;
            gp.time = 5;
            gp.posTime = 1;
            gp.actPoints = 240;
            gp.reaPoints = 480;
            break;

        default :
            gp.nbKind = 8;
            gp.endMult = 2;
            gp.pPD = 1;
            gp.time = 30;
            gp.posTime = 10;
            gp.actPoints = 120;
            gp.reaPoints = 240;
    }
            
    return gp;
}

void save_difficulty(difficulty diff) {
    ofstream file;

    file.open(DIFFICULTY_FILE.c_str(), ios::out | ios::trunc);
    
    if (file.is_open()) {
        file << diff;
        file.close();
    } else {
        cerr << '[' << DIFFICULTY_FILE << "] inaccessible en ecriture" << endl;
    }
}

difficulty load_difficulty() {
    ifstream file;
    int diff;

    file.open(DIFFICULTY_FILE.c_str());

    if (file.is_open()) {
        file >> diff;
        file.close();
    } else {
        cerr << '[' << DIFFICULTY_FILE << "] inaccessible en lecture" << endl;
        diff = int(normal);
    }

    return difficulty(diff);
}
