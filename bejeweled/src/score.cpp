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

#include "score.h"
#include "graphics.h"
#include "gameboard.h"
#include <iostream>
#include <sstream>

TTF_Font * init_font() {
    TTF_Font *pf;
    pf = TTF_OpenFont("themes/default/Hawaii_Killer.ttf", 40);

    if (!pf)
	cerr << "Erreur de chargement de la police !" << endl;
    return pf;
}

void free_font(TTF_Font *pf) {
    if (pf)
	TTF_CloseFont(pf);
}

void scores(TTF_Font *f, SDL_Surface *ps, int score)
{
 
    SDL_Rect pos;
	SDL_Surface *scoreFont;
	SDL_Color colorFont = {255,255,255,255};
	stringstream sstr;

    sstr << "Score : " << score;
    
	scoreFont = TTF_RenderText_Solid( f, sstr.str().c_str(), colorFont );
	
	if (!scoreFont)
	cerr << "Surface score non generee" << endl;
	scoreFont = TTF_RenderText_Solid( f, sstr.str().c_str(), colorFont );
	
	pos.x = 500;
	pos.y = 200;
    
    SDL_BlitSurface(scoreFont, 0, ps, &pos);
    SDL_FreeSurface(scoreFont);   
}
