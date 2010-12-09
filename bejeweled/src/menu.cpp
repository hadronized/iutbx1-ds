#include <iostream> // cerr
#include "graphics.h"
#include "menu.h"
#include "array.h"

using namespace std;

int const SHEET_WIDTH   = 350; // longueur feuille bouttons
int const SHEET_HEIGHT  = 160; // largeur feuille bouttons
int const BUTTON_WIDTH  = 150; // longueur d'un boutton
int const BUTTON_HEIGHT =  60; // hauteur d'un boutton

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


// Initialise un menu.
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

// Libère les bouttons d'un menu si initialisés.
void liberer_menu(menu &m) {
    if (m.wallpaper)
	SDL_FreeSurface(m.wallpaper);
    if (m.sheet)
	SDL_FreeSurface(m.sheet);
}

bool mouse_in_rect(SDL_Rect r, SDL_Event e) {
    return ( (e.motion.x >= r.x && e.motion.x <= r.x+r.w) && (e.motion.y >= r.y && e.motion.y <= r.y+r.h) );
}

// Détermine si le joueur selectionne le boutton Play.
bool play_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.play.at, e);
}

// Détermine si le joueur selectionne le boutton Quit.
bool quit_selected(menu m, SDL_Event e) {
    return mouse_in_rect(m.quit.at, e);
}

void menu_loop(SDL_Surface *ps) {
	SDL_Event event;
    bool jeu = false;
    bool quitter = false;
    menu m;

    initialisation_menu(m);

    while (!quitter) {
		
		
        SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
        
   		SDL_PollEvent(&event);
		affiche_menu(m, ps, event);
		
		if (play_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
		   quitter = true;
		 	
        else if ( quit_selected(m, event) && event.button.button == SDL_BUTTON_LEFT)
		   jeu = true;
		
        SDL_Flip(ps);
   
}
}

