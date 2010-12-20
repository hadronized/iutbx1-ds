#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "graphics.h"

struct button {
    SDL_Rect box; // définit rectangle dans la feuille de bouttons
    SDL_Rect  at; // définit où positionner le boutton à l'écran
};

struct menu {
    button play;
    button quit;
    SDL_Surface *wallpaper; // fond d'ecran du menu
    SDL_Surface *sheet;     // feuille du menu
};

void menu_loop(SDL_Surface *ps);

void initialisation_menu(menu &m);

void affiche_menu(menu m, SDL_Surface *ps, SDL_Event e);

void liberer_menu(menu &m);

bool mouse_in_rect(SDL_Rect r, SDL_Event e);

bool play_selected(menu m, SDL_Event e);

bool quit_selected(menu m, SDL_Event e);


