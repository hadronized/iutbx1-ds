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
#include <sstream>
#include "graphics.h"
#include "menu.h"
#include "array.h"
#include "gameplay.h"
#include "score.h"

using namespace std;

SDL_Surface * load_img(string const &fn) {
    SDL_Surface *pimg = IMG_Load(fn.c_str());

    if (!pimg) {
        cerr << "Erreur: chargement de l'image " << fn << " échoué" << endl;
    } 

    return pimg;
}

SDL_Surface * load_img_key(string const &fn, int r, int g, int b) {
    SDL_Surface* optimizedImage;

    optimizedImage = load_img(fn);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b));
    return optimizedImage;
}

TTF_Font * init_font_menu() {
    TTF_Font *pf;
    pf = TTF_OpenFont("themes/default/NEUROPOL.ttf", 150);

    if (!pf)
        cerr << "Erreur de chargement de la police !" << endl;
    return pf;
}

void initialisation_menu(menu &m) {
    // initialisation bouton play
    m.play.box.x = 0;
    m.play.box.y = 0;
    m.play.box.w = BUTTON_WIDTH;
    m.play.box.h = BUTTON_HEIGHT;
    m.play.at.x  = 100;
    m.play.at.y  = 300;
    m.play.at.w  = BUTTON_WIDTH;
    m.play.at.h  = BUTTON_HEIGHT;
    
    //initialisation bouton cooperation    
    m.coop.box.x = 260;
    m.coop.box.y =   0;
    m.coop.box.w = BUTTON_WIDTH;
    m.coop.box.h = BUTTON_HEIGHT;
    m.coop.at.x  = 320;
    m.coop.at.y  = 300;
    m.coop.at.w  = BUTTON_WIDTH;
    m.coop.at.h  = BUTTON_HEIGHT;
    
    //initialisation bouton versus
    m.versus.box.x = 520;
    m.versus.box.y =   0; 
    m.versus.box.w = BUTTON_WIDTH;
    m.versus.box.h = BUTTON_HEIGHT;
    m.versus.at.x  = 550;
    m.versus.at.y  = 300;
    m.versus.at.w  = BUTTON_WIDTH;
    m.versus.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton options
    m.options.box.x = 0;
    m.options.box.y = 78;
    m.options.box.w = BUTTON_WIDTH;
    m.options.box.h = BUTTON_HEIGHT;
    m.options.at.x  = 100;
    m.options.at.y  = 390;
    m.options.at.w  = BUTTON_WIDTH;
    m.options.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton scores
    m.score.box.x = 260;
    m.score.box.y =  78;
    m.score.box.w = BUTTON_WIDTH;
    m.score.box.h = BUTTON_HEIGHT;
    m.score.at.x  = 320;
    m.score.at.y  = 390;
    m.score.at.w  = BUTTON_WIDTH;
    m.score.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton quit
    m.quit.box.x = 520;
    m.quit.box.y =  78;
    m.quit.box.w = BUTTON_WIDTH;
    m.quit.box.h = BUTTON_HEIGHT;
    m.quit.at.x  = 550;
    m.quit.at.y  = 390;
    m.quit.at.w  = BUTTON_WIDTH;
    m.quit.at.h  = BUTTON_HEIGHT;
    
    m.wallpaper = load_img("themes/default/title.png");
    m.sheet = load_img("themes/default/buttons.png");
}

void affiche_menu(menu m,TTF_Font *f, SDL_Surface *ps, SDL_Event e) {
    if ( play_selected(m, e) ) // si la souris selectionne "1joueur"
        m.play.box.x = 130;
    else if( quit_selected(m, e) ) // si la souris selectionne "Quit"
        m.quit.box.x = 650;
    else if( coop_selected(m, e) ) // si la souris selectionne "Coop"
        m.coop.box.x = 390;
    else if( versus_selected(m, e) ) // si la souris selectionne "Versus"
        m.versus.box.x = 650;
    else if( options_selected(m, e) ) // si la souris selectionne "Options"
        m.options.box.x = 130;
    else if( score_selected(m, e) ) // si la souris selectionne "Scores"
        m.score.box.x = 390;
        
    SDL_BlitSurface(m.wallpaper, 0, ps, 0); // affichage du fond de menu
    SDL_BlitSurface(m.sheet, &m.play.box, ps, &m.play.at); // affichage du bouton play
    SDL_BlitSurface(m.sheet, &m.coop.box, ps, &m.coop.at); // affichage du bouton cooperation
    SDL_BlitSurface(m.sheet, &m.versus.box, ps, &m.versus.at); // affichage du bouton versus
    SDL_BlitSurface(m.sheet, &m.options.box, ps, &m.options.at); // affichage du bouton options
    SDL_BlitSurface(m.sheet, &m.score.box, ps, &m.score.at); // affichage du bouton scores
    SDL_BlitSurface(m.sheet, &m.quit.box, ps, &m.quit.at); // affichage du bouton quit
    
    SDL_Rect pos;
	SDL_Surface *titreFont;
	SDL_Color colorFont = {255,255,255,255};
	string message = "Diamant";
	
    stringstream sstr;
    sstr << message;
    
	titreFont = TTF_RenderText_Blended( f, sstr.str().c_str(), colorFont );
	
	if (!titreFont)
	cerr << "Surface titre non generee" << endl;
	
	pos.x =  30;
	pos.y = 100;
    
    SDL_BlitSurface(titreFont, 0, ps, &pos);
    SDL_FreeSurface(titreFont);
}

void liberer_menu(menu &m) {
    if (m.wallpaper)
	SDL_FreeSurface(m.wallpaper);
    if (m.sheet)
	SDL_FreeSurface(m.sheet);
}

bool mouse_in_rect(SDL_Rect r, SDL_Event e) {
    return ( (e.motion.x >= r.x && e.motion.x <= r.x+r.w) && (e.motion.y >= r.y && e.motion.y <= r.y+r.h) );
}

bool play_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.play.at, e);
}

bool quit_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.quit.at, e);
}

bool coop_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.coop.at, e);
}

bool versus_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.versus.at, e);
}

bool options_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.options.at, e);
}

bool score_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.score.at, e);
}

void menu_loop(SDL_Surface *ps) {
    SDL_Event event;
    bool quit = false;
    menu m;
    TTF_Font *pFontMenu = 0;
    TTF_Font *pFontScore = 0;
    TTF_Init();
    pFontMenu = init_font_menu();
    if (!pFontMenu)
        cerr << "Police non initialisee" << endl;
    pFontScore = init_font();
    if (!pFontScore)
        cerr << "Police non initialisee" << endl;
    		
    initialisation_menu(m);
    		
    while(!quit){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (play_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                    solo_loop(ps);
                } 

                else if (score_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) {
                    SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                    draw_top_ten(pFontScore, ps);
                }
                /* else if (versus_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                   {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   vs_loop(ps);
                   } 
                   
                   else if (coop_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                   {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   coop_loop(ps);
                   } 
                   
                   else if (options_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                   {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   options_loop(ps);
                   } 
                   
                */
     
                else if( quit_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
                {
                    quit = true;
                }
            }
            
            else if ( event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) )
                quit=true;
        }
		 
        affiche_menu(m, pFontMenu, ps, event);
        SDL_Flip(ps);
    }

    free_font(pFontMenu);
    free_font(pFontScore);
    TTF_Quit();
}
