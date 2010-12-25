#include <iostream> // cerr
#include "graphics.h"
#include "menu.h"
#include "array.h"
#include "gameplay.h"

using namespace std;

SDL_Surface * load_img(string const &fn) {
    SDL_Surface *ptmp = IMG_Load(fn.c_str());
    SDL_Surface *p = 0;

    if (!ptmp) {
        cerr << "Erreur: chargement de l'image " << fn << " échoué" << endl;
    } else {
        p = SDL_DisplayFormat(ptmp);
        if (!p)
            cerr << "Erreur: conversion de l'image échouée" << endl;
        SDL_FreeSurface(ptmp);
    }

    return p;
}

SDL_Surface * load_img_key(string const &fn, int r, int g, int b) {
    SDL_Surface* optimizedImage;

    optimizedImage = load_img(fn);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b));
    return optimizedImage;
}

void initialisation_menu(menu &m) {
    // initialisation bouton play
    m.play.box.x = 0;
    m.play.box.y = BUTTON_HEIGHT+(SHEET_HEIGHT-2*BUTTON_HEIGHT);
    m.play.box.w = BUTTON_WIDTH;
    m.play.box.h = BUTTON_HEIGHT;
    m.play.at.x  = (SCREEN_WIDTH-BUTTON_WIDTH)/2;
    m.play.at.y  = SCREEN_HEIGHT/2 + BUTTON_WIDTH/6;
    m.play.at.w  = BUTTON_WIDTH;
    m.play.at.h  = BUTTON_HEIGHT;

    // initialisation bouton quit
    m.quit.box.x = 0;
    m.quit.box.y = 0;
    m.quit.box.w = BUTTON_WIDTH;
    m.quit.box.h = BUTTON_HEIGHT;
    m.quit.at.x  = (SCREEN_WIDTH-BUTTON_WIDTH)/2;
    m.quit.at.y  = m.play.box.h+m.play.at.y+(SHEET_HEIGHT-2*BUTTON_HEIGHT);
    m.quit.at.w  = BUTTON_WIDTH;
    m.quit.at.h  = BUTTON_HEIGHT;
    
    m.wallpaper = load_img("themes/default/title.png");
    m.sheet = load_img_key("themes/default/button.bmp", 0, 0, 0);
}

void affiche_menu(menu m, SDL_Surface *ps, SDL_Event e) {
    if ( play_selected(m, e) ) // si la souris selectionne "Play"
        m.play.box.x = SHEET_WIDTH-BUTTON_WIDTH;
    else if ( quit_selected(m, e) ) // si la souris selectionne "Quit"
        m.quit.box.x = SHEET_WIDTH-BUTTON_WIDTH;
    SDL_BlitSurface(m.wallpaper, 0, ps, 0); // affichage du fond de menu
    SDL_BlitSurface(m.sheet, &m.play.box, ps, &m.play.at); // affichage du bouton play
    SDL_BlitSurface(m.sheet, &m.quit.box, ps, &m.quit.at); // affichage du bouton quit
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

void menu_loop(SDL_Surface *ps) {
    SDL_Event event;
    bool quit = false;
    menu m;
    		
    initialisation_menu(m);
    		
    while(!quit){
        SDL_PollEvent(&event);
            
        if (play_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) // a modifier en 1 joueur
        {
            SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
            solo_loop(ps);
        } 
	
	 /* else if (vs_selected(m, event) && event.button.button == SDL_BUTTON_LEFT) 
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
			
        affiche_menu(m, ps, event);
        SDL_Flip(ps);
    }
}

/*
     · Finalement, ce n'est pas vraiment de ta faute, plutôt de la façon dont je gère les
       déplacements à la souris, mais tu lances la fonction liée à un boutton lorsque le joueur
       enfonce le boutton gauche de la souris. Arrange toi pour que la fonction soit lancée
       lorsque le boutton gauche de la souris est relâché (car sinon ça sélectionne un diamant
       dans la grille, pas très cool ... ;).

   Donc occupe toi de ce petit menu.

*/
