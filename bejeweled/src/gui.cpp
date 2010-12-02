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

#include <iostream> // cerr
#include "gui.h"

using namespace std;

bool init_gui() {
    bool sdlb;
    bool ttfb;

    sdlb  = !SDL_Init(SDL_INIT_VIDEO);
    if (!sdlb)
	cerr << "[Init] SDL non correctement initialisee" << endl;
    else
	cout << "[Init] SDL correctement initialisee" << endl;

    ttfb = !TTF_Init();
    if (!ttfb)
	cerr << "[Init] TTF non correctement initialisee" << endl;
    else
	cout << "[Init] TTF correctement initialisee" << endl;

    return sdlb & ttfb;

}

void quit_gui() {
    TTF_Quit();
    SDL_Quit();
}

SDL_Surface * create_screen() {
    SDL_Surface *ps = SDL_SetVideoMode(SCREEN_WIDTH,
				       SCREEN_HEIGHT,
				       SCREEN_DEPTH,
				       SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ps)
	SDL_WM_SetCaption(SCREEN_TITLE.c_str(), 0);
    else
	cerr << "[Init] Aucun handler de fenetre disponible" << endl;
    return ps;
}

bool load_theme(string const &name, gameboard &gb) {
    string path;

    path = name + "pieces.png";
    gb.pieces = IMG_Load(path.c_str());
    SDL_SetColorKey(gb.pieces, SDL_SRCCOLORKEY, SDL_MapRGB(gb.pieces->format, 0, 255, 255));
    if (gb.pieces)
	cout << '[' << path << "] Image diamants correctement chargee" << endl;
    else
	cerr << '[' << path << "] Image diamants non correctement chargee" << endl;

    path = name + "grid.png";
    gb.grid = IMG_Load(path.c_str());
    if (gb.grid)
        cout << '[' << path << "] Image grille correctement chargee" << endl;
    else
	cerr << '[' << path << "] Image grille non correctement chargee" << endl;

    path = name + "title.png";
    gb.title_wp = IMG_Load(path.c_str());
    if (gb.title_wp)
	cout << '[' << path << "] Image fond d'ecran titre correctement chargee" << endl;
    else
	cerr << '[' << path << "] Image fond d'ecran titre non correctement chargee" << endl;

    path = name + "wallpaper.png";
    gb.game_wp = IMG_Load(path.c_str());
    if (gb.game_wp)
	cout << '[' << path << "] Image fond d'ecran jeu correctement chargee" << endl;
    else
	cerr << '[' << path << "] Image fond d'ecran jeu non correctement chargee" << endl;

    path = name + "explode.png";
    gb.explode = IMG_Load(path.c_str());
    if (gb.explode)
	cout << '[' << path << "] Image phases explosion correctement chargee" << endl;
    else
	cerr << '[' << path << "] Image phases explosion non correctement chargee" << endl;

    return true;
}

void free_theme(gameboard &gb) {
    if (gb.pieces) {
        SDL_FreeSurface(gb.pieces);
        gb.pieces = 0;
    }

    if (gb.grid) {
        SDL_FreeSurface(gb.grid);
        gb.grid = 0;
    }

    if (gb.title_wp) {
        SDL_FreeSurface(gb.title_wp);
        gb.title_wp = 0;
    }

    if (gb.game_wp) {
        SDL_FreeSurface(gb.game_wp);
        gb.game_wp = 0;
    }

    if (gb.explode) {
        SDL_FreeSurface(gb.explode);
        gb.explode = 0;
    }
}

/*
   A charger :
   
   - le fond d'�cran du menu
   - le fond d'�cran de jeu (wallpaper)
   - les boutons
   - tous les diamants sous forme de sprites
   - la grille
   - les effets d'explosions

   Nombre d'images totales :
      - 8 diamants
      - 2 fonds d'�crans
      - 1 feuille de boutons
 */


