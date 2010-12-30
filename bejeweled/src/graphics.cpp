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
#include <fstream>
#include <sstream>
#include "algorithm.h"
#include "cipher.h"
#include "graphics.h"
#include "gameboard.h"
#include "score.h"

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

bool cursor_in_grid(SDL_Event e, gameboard const &gb) {
    return (e.motion.x >= 0 && e.motion.x <= gb.row*DIAMOND_SIZE)
        && (e.motion.y >= 0 && e.motion.y <= gb.col*DIAMOND_SIZE);
}

void show_gameboard(gameboard &gb, SDL_Surface *ps) {
    diamond d;
    
    draw_game_wp(gb, 0, ps);
    draw_grid(gb, ps);
    for (int j = 0; j < gb.col; ++j) {
        for (int i = 0; i < gb.row; ++i) {
	    d = query_diamond(gb, i, j);
            draw_diamond(gb, d, ps);
        }
    }
}

void draw_game_wp(gameboard &gb, SDL_Rect *sub, SDL_Surface *ps) {
    SDL_BlitSurface(gb.game_wp, sub, ps, sub);
}

void draw_grid(gameboard &gb, SDL_Surface *ps) {
    SDL_BlitSurface(gb.grid, &gb.grid_rect, ps, &gb.grid_rect);
}

void draw_diamond(gameboard &gb, diamond &d, SDL_Surface *ps) {
    SDL_BlitSurface(gb.pieces, &d.sub, ps, &d.box);
}

void draw_diamond_swap(gameboard &gb, diamond &a, diamond &b, int vx, int vy, SDL_Surface *ps) {
    SDL_Rect area;
    area.x = min(a.box.x, b.box.x);
    area.y = min(a.box.y, b.box.y);
    area.w = a.box.x == b.box.x ? DIAMOND_SIZE : DIAMOND_SIZE*2;
    area.h = a.box.y == b.box.y ? DIAMOND_SIZE : DIAMOND_SIZE*2;

    for (int i = 0; i < DIAMOND_SIZE/2; ++i) {
        a.box.x += 2 * vx;
        a.box.y += 2 * vy;
        b.box.x -= 2 * vx;
        b.box.y -= 2 * vy;
        
	draw_game_wp(gb, 0, ps);
	draw_grid(gb, ps);
	draw_diamond(gb, a, ps);
	draw_diamond(gb, b, ps);
	
	SDL_UpdateRect(ps, area.x, area.y, area.w, area.h);
    }

    sdlrect_swap(a.box, b.box);
}

void draw_getdown(gameboard &gb, SDL_Surface *ps) {
    int x;
    int y;
    int vy = 1;
    diamond *pd;

    for (int move = 0; move < DIAMOND_SIZE; ++move) {
        for (int i = 0; i < gb.nb_expl; ++i) {
            index_1D2D(gb.expl[i], x, y, gb.row);
            while (y >= 0) {
                pd = &query_diamond(gb, x, y);
                pd->box.y += vy;
                --y;
            }
        }
        
        show_gameboard(gb, ps);
        SDL_Flip(ps);
        //cin.ignore(1024, '\n');
    }
    
    vy++;

}

void draw_solution(gameboard &gb, SDL_Surface *ps) {
    diamond *pd = &gb.dmds[gb.index_sol];

    for (int blink = 0; blink < 10; ++blink) {
        pd->sub.y = DIAMOND_SIZE - pd->sub.y;
        draw_game_wp(gb, 0, ps);
        draw_grid(gb, ps);
        draw_diamond(gb, *pd, ps);
        SDL_UpdateRect(ps, pd->box.x, pd->box.y, pd->box.w, pd->box.h);
        SDL_Delay(150);
    }
    
    pd->sub.y = 0;
}

void game_over(gameboard &gb, TTF_Font *pf, SDL_Surface *ps) {
    diamond *pd = &gb.dmds[gb.index_sol];
    SDL_Color red = { 255, 0, 0 };
    SDL_Rect pos;
    SDL_Surface *pgo = TTF_RenderText_Blended(pf, "Game Over", red);

    pos.x = (SCREEN_WIDTH-pgo->w)/2;
    pos.y = (SCREEN_HEIGHT-pgo->h)/2;

    for (int blink = 0; blink < 10; ++blink) {
        for (int col = 0; col < gb.col; ++col) {
            for (int row = 0; row < gb.row; ++row) {
                pd = &query_diamond(gb, col, row);
                pd->sub.y = DIAMOND_SIZE - pd->sub.y;
            }
        }

        show_gameboard(gb, ps);
        SDL_Flip(ps);
        SDL_Delay(150);
    }

    for (int yrel = 0; yrel < SCREEN_HEIGHT/4+pgo->h/2; ++yrel) {
        pos.y -= 1;
        //show_gameboard(gb, ps);
        draw_game_wp(gb, 0, ps);
        SDL_BlitSurface(pgo, 0, ps, &pos);
        SDL_Flip(ps);
        SDL_Delay(5);
    }
}

void draw_top_ten(TTF_Font *pf, SDL_Surface *ps) {
    fstream file;
    stringstream cdata;
    stringstream ddata;
    string name, score;
    SDL_Surface *pHighscores[10];
    SDL_Color white = { 255, 255, 255 };
    SDL_Rect pos;
    SDL_Event event;

    // petit hack pour s'assurer que le fichier existe
    file.open(TOP_TEN_SOLO_FILE.c_str(), ios::out | ios::app);
    file.close();

    file.open(TOP_TEN_SOLO_FILE.c_str(), ios::in);
    if (file.is_open()) {
        cdata << file.rdbuf();
        file.close();

        SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 0, 0, 0));

        ddata << decrypt(cdata.str());
        for (int i = 0; i < 10; ++i) {
            ddata >> name >> score;
            pHighscores[i] = TTF_RenderText_Blended(pf, (name+' '+score).c_str(), white);
            pos.x = (SCREEN_WIDTH-pHighscores[i]->w)/2;
            pos.y = i*pHighscores[i]->h;
            SDL_BlitSurface(pHighscores[i], 0, ps, &pos);
        }
        
        SDL_Flip(ps);

        do {
            SDL_WaitEvent(&event);
        } while (event.type != SDL_KEYUP || event.key.keysym.sym != SDLK_ESCAPE);
    } else {
        cerr << '[' << TOP_TEN_SOLO_FILE << "] inaccessible en lecture" << endl;
    }
    
}
