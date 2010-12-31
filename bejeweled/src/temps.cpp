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

#include "graphics.h"
#include <sstream>
#include <iostream>

void affiche_temps(TTF_Font *f, SDL_Surface *ps, int temps_restant)
{
	
	SDL_Rect pos;
	SDL_Surface *tempsFont;
	SDL_Color colorFont = {255,255,255,255};
    stringstream sstr;

    sstr << "Temps : " << temps_restant;
    
	tempsFont = TTF_RenderText_Blended( f, sstr.str().c_str(), colorFont );
	
	if (!tempsFont)
	cerr << "Surface temps non generee" << endl;
	
	pos.x = 500;
	pos.y = 100;
    
    SDL_BlitSurface(tempsFont, 0, ps, &pos);
    SDL_FreeSurface(tempsFont);   
}
