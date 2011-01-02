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
#include "game_param.h"

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

TTF_Font * init_font_options() {
    TTF_Font *pf;
    pf = TTF_OpenFont("themes/default/NEUROPOL.ttf", 50);

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

void init_menu_options(menu &o)
{
	// initialisation bouton difficulté facile
    o.facile.box.x = 0;
    o.facile.box.y = 0;
    o.facile.box.w = BUTTON_WIDTH;
    o.facile.box.h = BUTTON_HEIGHT;
    o.facile.at.x  = 100;
    o.facile.at.y  = 100;
    o.facile.at.w  = BUTTON_WIDTH;
    o.facile.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton difficulté normal
    o.normal.box.x = 260;
    o.normal.box.y = 0;
    o.normal.box.w = BUTTON_WIDTH;
    o.normal.box.h = BUTTON_HEIGHT;
    o.normal.at.x  = 420;
    o.normal.at.y  = 100;
    o.normal.at.w  = BUTTON_WIDTH;
    o.normal.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton difficulté héroique
    o.hero.box.x = 520;
    o.hero.box.y = 0;
    o.hero.box.w = BUTTON_WIDTH;
    o.hero.box.h = BUTTON_HEIGHT;
    o.hero.at.x  = 100;
    o.hero.at.y  = 200;
    o.hero.at.w  = BUTTON_WIDTH;
    o.hero.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton difficulté legendaire
    o.legend.box.x = 0;
    o.legend.box.y = 78;
    o.legend.box.w = BUTTON_WIDTH;
    o.legend.box.h = BUTTON_HEIGHT;
    o.legend.at.x  = 420;
    o.legend.at.y  = 200;
    o.legend.at.w  = BUTTON_WIDTH;
    o.legend.at.h  = BUTTON_HEIGHT;
    
    // initialisation bouton theme defaut
    o.defaut.box.x = 260;
    o.defaut.box.y = 78;
    o.defaut.box.w = BUTTON_WIDTH;
    o.defaut.box.h = BUTTON_HEIGHT;
    o.defaut.at.x  = 100;
    o.defaut.at.y  = 350;
    o.defaut.at.w  = BUTTON_WIDTH;
    o.defaut.at.h  = BUTTON_HEIGHT;
 
    // initialisation bouton theme fractal
    o.fractal.box.x = 520;
    o.fractal.box.y = 78;
    o.fractal.box.w = BUTTON_WIDTH;
    o.fractal.box.h = BUTTON_HEIGHT;
    o.fractal.at.x  = 420;
    o.fractal.at.y  = 350;
    o.fractal.at.w  = BUTTON_WIDTH;
    o.fractal.at.h  = BUTTON_HEIGHT;
    
    o.wallpaper = load_img("themes/default/title.png");
    o.sheet = load_img("themes/default/Buttons.png");  
}

void affiche_menu_options(menu o,TTF_Font *f, SDL_Surface *ps, SDL_Event e){
  if ( facile_selected(o, e) ) // si la souris selectionne "Facile"
        o.facile.box.x = 130;
    else if( normal_selected(o, e) ) // si la souris selectionne "Normal"
        o.normal.box.x = 650;
    else if( hero_selected(o, e) ) // si la souris selectionne "Hero"
        o.hero.box.x = 390;
    else if( legend_selected(o, e) ) // si la souris selectionne "Legend"
        o.legend.box.x = 650;
    else if( defaut_selected(o, e) ) // si la souris selectionne "Defaut"
        o.defaut.box.x = 130;
    else if( fractal_selected(o, e) ) // si la souris selectionne "Fractal"
        o.fractal.box.x = 390;
         
    SDL_BlitSurface(o.sheet, &o.facile.box, ps, &o.facile.at); // affichage du bouton facile
    SDL_BlitSurface(o.sheet, &o.normal.box, ps, &o.normal.at); // affichage du bouton normal
    SDL_BlitSurface(o.sheet, &o.hero.box, ps, &o.hero.at); // affichage du bouton heroïque
    SDL_BlitSurface(o.sheet, &o.legend.box, ps, &o.legend.at); // affichage du bouton legendaire
    SDL_BlitSurface(o.sheet, &o.defaut.box, ps, &o.defaut.at); // affichage du bouton defaut
    SDL_BlitSurface(o.sheet, &o.fractal.box, ps, &o.fractal.at); // affichage du bouton fractal 
    
    SDL_Rect pos;
    SDL_Surface *DiffFont;
	SDL_Color colorFont = {255,255,255,255};
	string message = "Difficulte :";
	
    stringstream sstr;
    sstr << message;
    
	DiffFont = TTF_RenderText_Blended( f, sstr.str().c_str(), colorFont );
	
	if (!DiffFont)
	cerr << "Surface titre non generee" << endl;
	
	pos.x =  30;
	pos.y =  30;
    
    SDL_BlitSurface(DiffFont, 0, ps, &pos);
    SDL_FreeSurface(DiffFont);
    
    
    SDL_Rect pos2;
    SDL_Surface *ThemeFont;
	string message2 = "Theme :";
	
    stringstream sstr1;
    sstr1 << message2;
    
	ThemeFont = TTF_RenderText_Blended( f, sstr1.str().c_str(), colorFont );
	
	if (!ThemeFont)
	cerr << "Surface theme non generee" << endl;
	
	pos2.x =  30;
	pos2.y =  260;
    
    SDL_BlitSurface(ThemeFont, 0, ps, &pos2);
    SDL_FreeSurface(ThemeFont);
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

void options_loop(SDL_Surface *ps){
	
  menu o;
  SDL_Event event;
  
  do {
      if (facile_selected(o, event) && event.button.button == SDL_BUTTON_LEFT){
          get_solo_param(easy);
          save_difficulty(easy);
      }
      else if (normal_selected(o, event) && event.button.button == SDL_BUTTON_LEFT){
          get_solo_param(normal);
          save_difficulty(normal);
      }
      else if (hero_selected(o, event) && event.button.button == SDL_BUTTON_LEFT){
          get_solo_param(heroic);
          save_difficulty(heroic);
      }
      else if (legend_selected(o, event) && event.button.button == SDL_BUTTON_LEFT){
          get_solo_param(legendary);
          save_difficulty(legendary);
      }
      else if (defaut_selected(o, event) && event.button.button == SDL_BUTTON_LEFT) {
          //free_theme(gb);
          //load_theme("themes/default/",gb);
      }
      else if (fractal_selected(o, event) && event.button.button == SDL_BUTTON_LEFT) {
          //free_theme(gb);
          //load_theme("themes/fractal_cosmos/", gb);
      }
      SDL_WaitEvent(&event);
  }while (event.type != SDL_KEYUP || event.key.keysym.sym != SDLK_ESCAPE);   
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

bool facile_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.facile.at, e);
}

bool normal_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.normal.at, e);
}

bool hero_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.hero.at, e);
}

bool legend_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.legend.at, e);
}

bool defaut_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.defaut.at, e);
}

bool fractal_selected(menu o, SDL_Event e) {
    return mouse_in_rect(o.fractal.at, e);
}

void menu_loop(SDL_Surface *ps) {
    SDL_Event event;
    bool quit = false;
    menu m;
    menu o;
    
    TTF_Font *pFontMenu = 0;
    TTF_Font *pFontScore = 0;
    TTF_Font *pFontOptions = 0;
    TTF_Init();
    pFontMenu = init_font_menu();
    if (!pFontMenu)
        cerr << "Police non initialisee" << endl;
    pFontScore = init_font();
    if (!pFontScore)
        cerr << "Police non initialisee" << endl;
    pFontOptions = init_font_options();
    if (!pFontOptions)
         cerr << "Police non initialisee" << endl;
       
    initialisation_menu(m);
    init_menu_options(o);
    
    
    while(!quit){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (play_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                    solo_loop(ps);
                } 

                else if (score_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                    draw_top_ten(pFontScore, ps);
                }
                
                else if (coop_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   coop_loop(ps);
                } 

                /* else if (versus_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                   {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   vs_loop(ps);
                   } 
                   
                   
                   
                   else if (options_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
                   {
                   SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
                   options_loop(ps);
                   } */
                   
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
    free_font(pFontOptions);
    TTF_Quit();
}
