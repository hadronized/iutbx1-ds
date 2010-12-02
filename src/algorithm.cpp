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

#include "algorithm.h"

void int_swap(int &a, int &b) {
    // using the XOR hack :)
    a ^= b;
    b ^= a;
    a ^= b;
}

void sdlrect_swap(SDL_Rect &a, SDL_Rect &b) {
    SDL_Rect tmp;
    tmp.x = a.x;
    tmp.y = a.y;
    tmp.w = a.w;
    tmp.h = a.h;
    a.x = b.x;
    a.y = b.y;
    a.w = b.w;
    a.h = b.h;
    b.x = tmp.x;
    b.y = tmp.y;
    b.w = tmp.w;
    b.h = tmp.h;
}
