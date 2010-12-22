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
    
	tempsFont = TTF_RenderText_Solid( f, sstr.str().c_str(), colorFont );
	
	if (!tempsFont)
	cerr << "Surface temps non generee" << endl;
	
	pos.x = 500;
	pos.y = 100;
    
    SDL_BlitSurface(tempsFont, 0, ps, &pos);
    SDL_FreeSurface(tempsFont);   
}
