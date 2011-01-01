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

#include "keyboard.h"

void init_keyboard(keyboard &kb, gameboard const &gb) {
    kb.hover = 0;
    kb.lock = -1; // aucun diamant selectionne par defaut
    kb.col = gb.col;
    kb.row = gb.row;
}


void keyboard_update_up(keyboard &kb) {
    if (kb.hover / kb.col > 0)
        kb.hover -= kb.row;
}

void keyboard_update_down(keyboard &kb) {
    if (kb.hover / kb.col < kb.col-1)
        kb.hover += kb.row;
}

void keyboard_update_left(keyboard &kb) {
    if (kb.hover % kb.col > 0)
        --kb.hover;
}

void keyboard_update_right(keyboard &kb) {
    if (kb.hover % kb.col < kb.row-1)
        ++kb.hover;
}

void keyboard_lock(keyboard &kb, bool lock) {
    kb.lock = lock ? kb.hover : -1;
}
