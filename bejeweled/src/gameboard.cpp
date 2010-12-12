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
#include "array.h"

#include <iostream> // pour tests uniquement
using namespace std;

void init_gameboard(gameboard &gb) {
    int index;
    diamond_type tmp;

    gb.nb_expl = 0;
    gb.index_sol = -1;

    for (int j = 0; j < MATRIX_HEIGHT; ++j) {
        for (int i = 0; i < MATRIX_WIDTH; ++i) {
            index = index_2D1D(i, j);
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
    return gb.dmds[index_2D1D(x, y)];
}

void show_gameboard(gameboard &gb, SDL_Surface *ps) {
    diamond d;
    
    SDL_BlitSurface(gb.game_wp, 0, ps, 0);
    SDL_BlitSurface(gb.grid, 0, ps, 0);
    for (int j = 0; j < MATRIX_HEIGHT; ++j) {
        for (int i = 0; i < MATRIX_WIDTH; ++i) {
	    d = query_diamond(gb, i, j);
            SDL_BlitSurface(gb.pieces, &d.sub, ps, &d.box);
        }
    }
}

bool check_explode(gameboard &gb) {
    int index;
    diamond tmp;
    diamond_type rooth;
    diamond_type rootv;
    int counth = 1;
    int countv = 1;

    gb.nb_expl = 0;
    
    for (int j = 0; j < MATRIX_HEIGHT; ++j) {
        rooth = -1; // reinitialisation diamant en debut de ligne
        rootv = -1; // reinitialisation diamant en debut de colonne
        for (int i = 0; i < MATRIX_WIDTH; ++i) {
            // test horizontal
            index = index_2D1D(i, j);
            tmp = query_diamond(gb, i, j);

            if (tmp.type == rooth) {
                ++counth;
            } else {
                if (counth >= 3) {
                    --index;
                    for (int y = 0; y < counth; ++y)
                        array_insert(index-y, gb.expl, gb.nb_expl, MATRIX_DIMENSION);
                }
                rooth = tmp.type;
                counth = 1;
            }

            // test vertical
            index = index_2D1D(j, i);
            tmp = query_diamond(gb, j, i);

            if (tmp.type == rootv) {
                ++countv;
            } else {
                if (countv >= 3) {
                    if (i == 0)
                        index = index_2D1D(j-1, MATRIX_HEIGHT-1);
                    else
                        index -= MATRIX_WIDTH;
                    for (int y = 0; y < countv; ++y)
                        array_insert(index-y*MATRIX_WIDTH, gb.expl, gb.nb_expl, MATRIX_DIMENSION);
                }
                rootv = tmp.type;
                countv = 1;
            }
        }
    }

    if (counth >= 3) {
        for (int y = 0; y < counth; ++y)
            array_insert(index-y, gb.expl, gb.nb_expl, MATRIX_DIMENSION);
    }

    if (countv >= 3) {
        for (int y = 0; y < countv; ++y)
            array_insert(index-y*MATRIX_WIDTH, gb.expl, gb.nb_expl, MATRIX_DIMENSION);
    }

    return gb.nb_expl != 0;
}

bool try_swap(gameboard &gb, diamond &a, diamond &b) {
    bool success = false;
    
    if ( is_near(a, b) ) { // tentative possible
        diamond_swap(a, b); // on echange les diamants
	if ( check_explode(gb) ) // si il y a eu au moins une explosion
            success = true;
        else { // si aucune explosion generee, on reechange les diamants
            diamond_swap(a, b);
        }
    } 
    
    return success;
}

void explode(gameboard &gb, SDL_Surface *ps) {
    SDL_Rect pos;
    SDL_Rect sub;
    int tmpx, tmpy;

    sub.y = 0;
    sub.w = DIAMOND_SIZE;
    sub.h = DIAMOND_SIZE;

    for (int y = 0; y < 9; ++y) {
        sub.x = y*DIAMOND_SIZE;
        for (int i = 0; i < gb.nb_expl; ++i) {
            index_1D2D(gb.expl[i], tmpx, tmpy);
            
            pos.x = tmpx*DIAMOND_SIZE;
            pos.y = tmpy*DIAMOND_SIZE;

            SDL_BlitSurface(gb.explode, &sub, ps, &pos);
        }
        
        SDL_Flip(ps);
        SDL_Delay(80);
    }
}

void get_down(gameboard &gb, SDL_Surface *ps) {
    int x, y;
    diamond *pd;

    for (int i = 0; i < gb.nb_expl; ++i) {
        index_1D2D(gb.expl[i], x, y);
        while (y > 0) {
            diamond_swap(query_diamond(gb, x, y), query_diamond(gb, x, y-1));
            --y;
        }
        
        pd = &query_diamond(gb, x, 0);
        change_diamond_type(*pd, pd->type, pd->type);
    }
}

bool equal(diamond a, diamond b, diamond c) {
    return a.type == b.type && b.type == c.type;
}

bool check_hpattern_3x2(gameboard &gb, int i, int j) {
    diamond abc[3];
    int reli;
    int relj;
    int a = 0;
    int b = 0;

    // D X D  et  X D X
    // X D X      D X D
    for (int off = 0; off < 2; ++off) {
        reli = 0;
        relj = off;
        while (reli < 3) {
            abc[reli] = query_diamond(gb, i+reli, j+relj);
            ++reli;
            relj = 1-relj;
        }

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(i+1, j+relj);
            return true;
        }
    }

    // X X D  et  D X X  et  X D D  et  D D X
    // D D X      X D D      D X X      X X D
    relj = 0;
    for (int off = 0; off < 4; ++off) {
        reli = 0;
        
        while (reli < 3) {
            abc[reli] = query_diamond(gb, i+reli, j+relj);
            ++reli;
            relj = 1-a;
            a = b;
            b = relj;
        }

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(i+(off%2)*2, j+relj);
            return true;
        }
    }

    return false;
}

bool check_vpattern_3x2(gameboard &gb, int i, int j) {
    diamond abc[3];
    int reli;
    int relj;
    int a = 0;
    int b = 0;

    // D X D  et  X D X
    // X D X      D X D
    for (int off = 0; off < 2; ++off) {
        reli = 0;
        relj = off;
        while (reli < 3) {
            abc[reli] = query_diamond(gb, j+relj, i+reli);
            ++reli;
            relj = 1-relj;
        }

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(j+relj, i+1);
            return true;
        }
    }

    // X X D  et  D X X  et  X D D  et  D D X
    // D D X      X D D      D X X      X X D
    relj = 0;
    for (int off = 0; off < 4; ++off) {
        reli = 0;
        
        while (reli < 3) {
            abc[reli] = query_diamond(gb, j+relj, i+reli);
            ++reli;
            relj = 1-a;
            a = b;
            b = relj;
        }

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(j+relj, i+(off%2)*2);
            return true;
        }
    }

    return false;
}

bool check_hpattern_4x1(gameboard &gb, int i, int j) {
    diamond abc[3];

    // D X D D  et  D D X D
    for (int off = 0; off < 2; ++off) {
        abc[0] = query_diamond(gb, i, j);
        abc[1] = query_diamond(gb, i+3, j);
        abc[2] = query_diamond(gb, i+off+1, j);

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(i+(1-off)*3, j);
            return true;
        }
    }

    return false;
}

bool check_vpattern_4x1(gameboard &gb, int i, int j) {
    diamond abc[3];

    // D X D D  et  D D X D
    for (int off = 0; off < 2; ++off) {
        abc[0] = query_diamond(gb, j, i);
        abc[1] = query_diamond(gb, j, i+3);
        abc[2] = query_diamond(gb, j, i+off+1);

        if (equal(abc[0], abc[1], abc[2])) {
            gb.index_sol = index_2D1D(j, i+(1-off)*3);
            return true;
        }
    }

    return false;
}

bool check_solution(gameboard &gb) {
    for (int j = 0; j < MATRIX_HEIGHT-1; ++j) {
        for (int i = 0; i < MATRIX_WIDTH-2; ++i) {
            if ( check_hpattern_3x2(gb, i, j) || check_vpattern_3x2(gb, i, j)) {
                return true;
            } else if  (i < MATRIX_WIDTH-3 && j < MATRIX_HEIGHT) {
                if ( check_hpattern_4x1(gb, i, j) || check_vpattern_4x1(gb, i, j) )
                    return true;
            }
        }
    }

    return false;
}
