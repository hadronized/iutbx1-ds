#include "graphics.h"
#include "gameboard.h"
#include "temps.h"
#include <iostream>
#include <sstream>

void scores(TTF_Font *f, SDL_Surface *ps)
{
	gameboard gb;
    int score=0;
    
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
