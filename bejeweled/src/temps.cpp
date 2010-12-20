#include <time.h>
#include <iostream>
#include "graphics.h"
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

void affiche_temps(TTF_Font *f, SDL_Surface *ps)
{
	
	SDL_Rect pos;
	SDL_Surface *tempsFont;
	SDL_Color colorFont = {255,255,255,255};

	int temps;
	int temps_restant;
	int tps ;
    stringstream sstr;
	
	temps = 180;
	tps = time(0);
	
	temps_restant = temps - ( time(0) - tps);

    sstr << "Temps : " << temps_restant;
    
	tempsFont = TTF_RenderText_Solid( f, sstr.str().c_str(), colorFont );
	
	if (!tempsFont)
	cerr << "Surface temps non generee" << endl;
	
	pos.x = 500;
	pos.y = 100;
    
    SDL_BlitSurface(tempsFont, 0, ps, &pos);
    SDL_FreeSurface(tempsFont);   
}

