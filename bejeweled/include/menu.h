#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "graphics.h"

int const SHEET_WIDTH   = 350; // longueur feuille bouttons
int const SHEET_HEIGHT  = 160; // largeur feuille bouttons
int const BUTTON_WIDTH  = 150; // longueur d'un boutton
int const BUTTON_HEIGHT =  60; // hauteur d'un boutton


struct button {
    SDL_Rect box; // définit rectangle dans la feuille de bouttons
    SDL_Rect  at; // définit où positionner le boutton à l'ecran
};

struct menu {
    button play;
    button quit;
    SDL_Surface *wallpaper; // fond d'ecran du menu
    SDL_Surface *sheet;     // feuille du menu
};

/* *********************** menu_loop *************************
   * menu_loop(SDL_Surface *ps);                             *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction est la boucle contenant le menu          *
   *********************** Entrees ***************************
   * `ps' : pointeur sur la surface                          *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void menu_loop(SDL_Surface *ps);

/* *********************** initialisation_menu ***************
   * initialisation_menu(menu &m);                           *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet d'initialiser le menu             *
   *********************** Entrees ***************************
   * `m' : reference sur le menu à initialiser               *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void initialisation_menu(menu &m);

/* *********************** affiche_menu **********************
   * affiche_menu(menu m, SDL_Surface *ps, SDL_Event e);     *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet d'afficher le menu                *
   *********************** Entrees ***************************
   * `m' : menu à afficher precedement initialiser           *
   *                                                         *
   * `ps': pointeur sur la surface                           *
   *                                                         *
   * `e' : evenement par lequel on recupere l'etat de        *
   *       souris                                            *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void affiche_menu(menu m, SDL_Surface *ps, SDL_Event e);

/* *********************** liberer_menu **********************
   * initialisation_menu(menu &m);                           *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet de liberer                        *
   *********************** Entrees ***************************
   * `m' : reference sur le menu à liberer                   *
   *********************** Sorties ***************************
   * void                                                    *
   *********************************************************** */
void liberer_menu(menu &m);


/* *********************** mouse_in_rect *********************
   * bool mouse_in_rect(SDL_Rect r, SDL_Event e);            *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction de savoir si la souris est dans le       * 
   * rectangle pré-defini                                    *
   *********************** Entrees ***************************
   * `r' : rectangle                                         *
   *                                                         *
   * `e' : evenement par lequel on recupere l'etat de        *
   *       souris                                            *
   *********************** Sorties ***************************
   * bool                                                    *
   *********************************************************** */
bool mouse_in_rect(SDL_Rect r, SDL_Event e);

/* *********************** play_selected *********************
   * bool play_selected(menu m, SDL_Event e);                *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet de savoir si la souris            *
   * selectionne le bouton play                              *
   *********************** Entrees ***************************
   * `m' : menu precedemment initialisé                      *
   *                                                         *
   * `e' : evenement par lequel on recupere l'etat de        *
   *       souris                                            *
   *********************** Sorties ***************************
   * bool                                                    *
   *********************************************************** */
bool play_selected(menu m, SDL_Event e);

/* *********************** quit_selected *********************
   * bool quit_selected(menu m, SDL_Event e);                *
   *********************** Auteur , Dates ********************
   * Ludwig Raepsaet, 13  Decembre 2010, v0.1                *
   *********************** Description ***********************
   * Cette fonction permet de savoir si la souris            *
   * selectionne le bouton quit                              *
   *********************** Entrees ***************************
   * `m' : menu precedemment initialisé                      * 
   *                                                         *
   * `e' : evenement par lequel on recupere l'etat de        *
   *       souris                                            *
   *********************** Sorties ***************************
   * bool                                                    *
   *********************************************************** */
bool quit_selected(menu m, SDL_Event e);


