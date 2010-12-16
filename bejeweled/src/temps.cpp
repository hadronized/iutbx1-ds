#include <time.h>
#include "graphics.h"
#include <iostream>

void affiche_temps(SDL_Surface *ps)
{
TTF_Font *font = TTF_OpenFont( "themes/default/Hawaii_Killer.ttf", 20 );
SDL_Color colorFont = {0,0,0,0};
SDL_Surface *tempsFont;

char temps1[20] = "Temps: ";
int temps;
int temps_restant;
int tps ;
	
	
	temps = 180;
	tps = time(0);
	
	temps_restant = temps - ( time(0) - tps);
       
	if (temps_restant <= 0)
	{
		SDL_Quit();
	}
	
	else
	{
   		    sprintf(temps1,"%d", temps_restant);
			tempsFont = TTF_RenderText_Solid( font, temps1, colorFont );
			cout << "[Init] Temps correctement affiche" << endl;
			
	}
}

