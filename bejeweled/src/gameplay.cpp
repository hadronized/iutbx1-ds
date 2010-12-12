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

#include <iostream> // pour tests
#include "gameplay.h"
#include "array.h"

using namespace std;

bool main_loop(SDL_Surface *ps) {
    SDL_Event event;
    bool quit = false;
    gameboard gb;
    diamond *pSelected = 0;

    load_theme("themes/fractal_cosmos/", gb);
    init_gameboard(gb);

    while (!quit) {
        SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));

	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                if (cursor_in_grid(event)) {
                    if (!pSelected) {
                        pSelected = &query_diamond(gb, event.motion.x/DIAMOND_SIZE, event.motion.y/DIAMOND_SIZE);
                        pSelected->sub.y = DIAMOND_SIZE;
                    } else {
                        pSelected->sub.y = 0;
                        try_swap(gb, *pSelected, query_diamond(gb, event.motion.x/DIAMOND_SIZE, event.motion.y/DIAMOND_SIZE));
                        do {
                            show_gameboard(gb, ps);
                            explode(gb, ps);
                            get_down(gb, ps);
                        } while ( check_explode(gb) );

                        if (!check_solution(gb)) {
                            #ifdef _DEBUG
                            cout << "Plus aucune solution" << endl;
                            #endif
                        } else {
                            #ifdef _DEBUG
                            cout << '(' << gb.index_sol%8 << ';' << gb.index_sol/8 << ") est une solution" << endl;
                            #endif
                        }
                        
                        pSelected = 0;
                    }
                }
            }
	}
	
	show_gameboard(gb, ps);
        SDL_Flip(ps);
    }

    free_theme(gb);
    return true;
}

bool cursor_in_grid(SDL_Event e) {
    return (e.motion.x >= 0 && e.motion.x <= GRID_WIDTH)
        && (e.motion.y >= 0 && e.motion.y <= GRID_HEIGHT);
}
