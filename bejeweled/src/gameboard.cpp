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

#include <cstdlib> // pour rand()
#include "algorithm.h"
#include "gameboard.h"
#include "graphics.h"
#include "array.h"

void init_gameboard(gameboard &gb, int col, int row) {
    int index;
    diamond_type tmp;

    gb.nb_expl = 0;
    gb.index_sol = -1;

    gb.dmds = new diamond[col*row];
    gb.col = col;
    gb.row = row;
    
    gb.expl = new int[col*row];
    
    gb.grid_rect.x = 0;
    gb.grid_rect.y = 0;
    gb.grid_rect.w = row*DIAMOND_SIZE;
    gb.grid_rect.h = col*DIAMOND_SIZE;

    for (int j = 0; j < col; ++j) {
        for (int i = 0; i < row; ++i) {
            index = index_2D1D(i, j, row);
            tmp = init_diamond(gb.dmds[index], i, j);

            if (i >= 2) { // test horizontal
                if ( (gb.dmds[index-1].type == tmp) && (gb.dmds[index-2].type == tmp) )
                    change_diamond_type(gb.dmds[index], tmp, tmp);
            }
            
            if (j >= 2) { // test vertical
                if ( (query_diamond(gb, i, j-1).type == gb.dmds[index].type) && (query_diamond(gb, i, j-2).type == gb.dmds[index].type) ) {
                    change_diamond_type(gb.dmds[index], gb.dmds[index-1].type, gb.dmds[index].type);
                }
            }
        }
    }
}

diamond & query_diamond(gameboard &gb, int x, int y) {
    return gb.dmds[index_2D1D(x, y, gb.row)];
}
