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

#include "game_param.h"

game_param get_solo_param(difficulty diff) {
    game_param gp;

    switch (diff) {
        case easy :
            gp.nbKind = 4;
            gp.endMult = 1;
            gp.pPD = 1;
            gp.time = 90;
            gp.posTime = 20;
            gp.negTime = 0;
            gp.actPoints = 30;
            gp.reaPoints = 100;
            break;

        case normal :
            gp.nbKind = 5;
            gp.endMult = 2;
            gp.pPD = 1;
            gp.time = 60;
            gp.posTime = 15;
            gp.negTime = 0;
            gp.actPoints = 60;
            gp.reaPoints = 175;
            break;

        case heroic :
            gp.nbKind = 7;
            gp.endMult = 3;
            gp.pPD = 2;
            gp.time = 20;
            gp.posTime = 10;
            gp.negTime = 5;
            gp.actPoints = 120;
            gp.reaPoints = 300;
            break;

        case legendary :
            gp.nbKind = 8;
            gp.endMult = 4;
            gp.pPD = 2;
            gp.time = 10;
            gp.posTime = 5;
            gp.negTime = 5;
            gp.actPoints = 200;
            gp.reaPoints = 400;
            break;


    }
            
    return gp;
}
