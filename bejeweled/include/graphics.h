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

#ifndef GUI_H
#define GUI_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "gameplay.h"

using namespace std;
int const  SCREEN_WIDTH   = 720;
int const  SCREEN_HEIGHT  = 480;
int const  SCREEN_DEPTH   = 32;
string const SCREEN_TITLE = "Bejeweled !";

bool init_gui(void);
void quit_gui(void);
SDL_Surface * create_screen(void);
bool load_theme(string const &name, gameboard &gb);
void free_theme(gameboard &gb);
void show_gameboard(gameboard &gb, SDL_Surface *ps);
void draw_game_wp(gameboard &gb, SDL_Rect *sub, SDL_Surface *ps);
void draw_grid(gameboard &gb, SDL_Surface *ps);
void draw_diamond(gameboard &gb, diamond &d, SDL_Surface *ps);
void draw_diamond_swap(gameboard &gb, diamond &a, diamond &b, int vx, int vy, SDL_Surface *ps);
void draw_getdown(gameboard &gb, SDL_Surface *ps); // a compléter ! :)

#endif // guard
