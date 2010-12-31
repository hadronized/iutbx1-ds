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
#include "diamond.h"

using namespace std;

diamond_type init_diamond(diamond &d, int x, int y, int kind) {
    d.type = rand() % kind;
    d.box.x = x*DIAMOND_SIZE;
    d.box.y = y*DIAMOND_SIZE;
    d.sub.x = d.type*DIAMOND_SIZE;
    d.sub.y = 0;
    d.sub.w = d.sub.h = DIAMOND_SIZE;

    return d.type;
}

void change_diamond_type(diamond &d, diamond_type h, diamond_type v, int kind) {
    while (d.type == h || d.type == v)
	d.type = rand() % kind;
    d.sub.x = d.type*DIAMOND_SIZE;
}

bool is_near(diamond const &a, diamond const &b) {
    return (a.box.x == b.box.x && max(a.box.y, b.box.y) - min(a.box.y, b.box.y) == DIAMOND_SIZE)
        || (a.box.y == b.box.y && max(a.box.x, b.box.x) - min(a.box.x, b.box.x) == DIAMOND_SIZE);
}

void diamond_swap(diamond &a, diamond &b) {
    int_swap(a.type, b.type);
    sdlrect_swap(a.sub, b.sub);
}

bool equal(diamond a, diamond b, diamond c) {
    return a.type == b.type && b.type == c.type;
}
