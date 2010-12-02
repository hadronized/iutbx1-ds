/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Projet AP1S1 1 : Pong. A pong-like game written in C++ with the SDL,
    SDL_image and SDL_ttf libraries.

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

// pong.cc 

#include <iostream> // pour cerr
#include <cstdlib>
#include <string>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

using namespace std;

int const SCREEN_WIDTH  = 640; // longueur écran
int const SCREEN_HEIGHT = 400; // hauteur écran
int const SCREEN_BPP    =  32; // bits par pixel
int const TAILLE        =   6; // taille de la balle
int const WALL_WIDTH    =  11; // largeur raquette
int const WALL_HEIGHT   =  43; // hauteur raquette
int const WALL_MARGIN   =  10; // marge joueur-bord écran
int const SHEET_WIDTH   = 350; // longueur feuille bouttons
int const SHEET_HEIGHT  = 160; // largeur feuille bouttons
int const BUTTON_WIDTH  = 150; // longueur d'un boutton
int const BUTTON_HEIGHT =  60; // hauteur d'un boutton
int const SCORE_MAX     =  3; // score maximal à atteindre

struct ball 
{
    int x;               // abscisse du centre de la balle
    int y;               // ordonnée du centre de la balle
    int w;               // largeur de la balle
    int h;               // hauteur de la balle
    int mvt_x;           // mouvement sur l'axe des abscisses
    int mvt_y;           // mouvement sur l'axe des ordonnées
    SDL_Surface *sprite; // sprite représentant la balle
};

struct wall {
    SDL_Rect box;        // x, y, w et h
    int mvt_x;           // mouvement sur l'axe des abscisses
    int mvt_y;           // mouvement sur l'axe des ordonnées
    int score;           // score du joueur
    SDL_Surface *sprite; // sprite représentant un joueur
};

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

// Charge une image dans un SDL_Surface et retourne un pointeur sur ce dernier.
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

// Charge une image dans un SDL_Surface et retourne un pointeur sur ce dernier.
// Cette fonction gère aussi un paramètre de color keying afin de rendre transparente
// une couleur passée comme paramètre (triplet).
SDL_Surface * load_img_key(string const &fn, int r, int g, int b) {
    SDL_Surface* optimizedImage;

    optimizedImage = load_img(fn);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b));
    return optimizedImage;
}

// Initialise une balle.
void initBall(ball &b)
{
    b.x=SCREEN_WIDTH/2;
    b.y=SCREEN_HEIGHT/2;
    b.w=TAILLE;
    b.h=TAILLE;
    b.mvt_x=2;
    b.mvt_y=2;
    b.sprite = load_img_key("data/ball.bmp", 0, 255, 255);
} 

// Initialise un joueur en fonction de son sprite et de son abscisse.
void init_wall(wall &w, string const &fn, int x) {
    w.box.x = x;
    w.box.y = (SCREEN_HEIGHT-WALL_HEIGHT)/2;
    w.box.w = WALL_WIDTH;
    w.box.h = WALL_HEIGHT;
    w.mvt_x = 4;
    w.mvt_y = 4;
    w.score = 0;
    w.sprite = load_img_key(fn, 0, 255, 255);
}

// Initialise un menu.
void init_menu(menu &m) {
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
    
    m.wallpaper = load_img("data/title.bmp");
    m.sheet = load_img_key("data/button.bmp", 0, 0, 0);
}

// Initialise la police utilisée dans le jeu, et retourne un pointeur sur
// cette dernière
TTF_Font * init_font() {
    TTF_Font *pf;
    pf = TTF_OpenFont("data/cgf_locust_resistance.ttf", 40);

    if (!pf)
	cerr << "Erreur de chargement de la police !" << endl;
    return pf;
}

// Libère la balle si initialisée.
void free_ball(ball &b) {
    if (b.sprite)
	SDL_FreeSurface(b.sprite);
}

// Libère un joueur si initialisé.
void free_wall(wall &w) {
    if (w.sprite)
	SDL_FreeSurface(w.sprite);
}

// Libère les bouttons d'un menu si initialisés.
void free_menu(menu &m) {
    if (m.wallpaper)
	SDL_FreeSurface(m.wallpaper);
    if (m.sheet)
	SDL_FreeSurface(m.sheet);
}

// Libère une police si initialisée
void free_font(TTF_Font *pf) {
    if (pf)
	TTF_CloseFont(pf);
}

// Réinitialise la position de la balle et modifie son mouvement pour qu'elle aille
// dans la direction du joueur qui vient de marquer un point.
void reset_ball(ball &b) {
    b.x = (SCREEN_WIDTH-b.w)/2;
    b.y = (SCREEN_HEIGHT-b.h)/2;
    b.mvt_x *= -1; // inverse le sens de la direction
}

// Réinitialise les joueurs (ainsi que leur score).
void reset_players(wall &p01, wall &p02) {
    p01.box.y = (SCREEN_HEIGHT-WALL_HEIGHT)/2;
    p01.score = 0;
    p02.box.y = (SCREEN_HEIGHT-WALL_HEIGHT)/2;
    p02.score = 0;
}

// Détermine si deux rectangles se chevauchent, ou pas.
bool collision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB; 
    int rightA, rightB; 
    int topA, topB; 
    int bottomA, bottomB; 
  
    leftA = a.x; 
    rightA = a.x + a.w; 
    topA = a.y;
    bottomA = a.y + a.h; 
  
    leftB = b.x; 
    rightB = b.x + b.w; 
    topB = b.y; 
    bottomB = b.y + b.h; 
  
    if(bottomA <= topB) 
        return false; 
    if(topA >= bottomB) 
        return false;  
    if(rightA <= leftB) 
        return false;  
    if(leftA >= rightB) 
        return false;
 
    return true; 
}

// Déplace la balle en prévoyant les collisions, et si collision il y a, corrige
// le mouvement de la balle.
void moveBall(ball &b, wall player01, wall player02)
{
    SDL_Rect tmp;

    b.x+=b.mvt_x;

    tmp.x=b.x-TAILLE/2;
    tmp.y=b.y-TAILLE/2;
    tmp.h=TAILLE;
    tmp.w=TAILLE;
  
    // Correction Mouvement Horizontal
    if( collision(tmp, player01.box) || collision(tmp, player02.box) )
    {
        b.x -= b.mvt_x;
        b.mvt_x*=-1;
    }

    b.y+=b.mvt_y;

    tmp.x=b.x-TAILLE/2;
    tmp.y=b.y-TAILLE/2;
  
    // Correction Mouvement Vertical
    if((b.y+TAILLE/2 > SCREEN_HEIGHT) || (b.y-TAILLE/2 < 0) || collision(tmp,player01.box) || collision(tmp, player02.box) )
    {
        b.y-=b.mvt_y;
        b.mvt_y*=-1;
    }
}

// Déplace un joueur en fonction de si la touche monter ou si la touche descendre est appuyée.
// Il est important de noter que si le joueur appuit sur les deux touches en même temps, aucun
// mouvement n'est réalisé.
void move_wall(wall &w, bool up, bool down) {
    if ( (up && down) == false) { // si le joueur n'appuie pas sur les deux touches monter et descendre en meme temps
        if (up) { // si le joueur souhaite monter
            w.box.y -= w.mvt_y;
        } else if (down) { // si le joueur souhaite descendre
            w.box.y += w.mvt_y;
        }

        // Gestion sortie
        if (w.box.y <= 0) {
            w.box.y = 0;
        } else if (w.box.y+w.box.h >= SCREEN_HEIGHT) {
            w.box.y = SCREEN_HEIGHT-w.box.h;
        }
    }
}

// Détermine si le curseur de la souris se situe dans un rectangle, ou pas.
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

// Affiche le menu (fond d'écran + bouttons).
void show_menu(menu m, SDL_Surface *s, SDL_Event e) {
    if ( play_selected(m, e) ) // si la souris selectionne "Play"
        m.play.box.x = SHEET_WIDTH-BUTTON_WIDTH;
    else if ( quit_selected(m, e) ) // si la souris selectionne "Quit"
        m.quit.box.x = SHEET_WIDTH-BUTTON_WIDTH;
    SDL_BlitSurface(m.wallpaper, 0, s, 0); // affichage du fond de menu
    SDL_BlitSurface(m.sheet, &m.play.box, s, &m.play.at); // affichage du bouton play
    SDL_BlitSurface(m.sheet, &m.quit.box, s, &m.quit.at); // affichage du bouton quit
}

// Affiche la balle à l'écran.
void showBall(ball b, SDL_Surface *s)
{
    SDL_Rect r;
    r.x=b.x-TAILLE/2;
    r.y=b.y-TAILLE/2;
    r.w=TAILLE;
    r.h=TAILLE;

    SDL_BlitSurface(b.sprite, 0, s, &r);
}

// Affiche un joueur à l'écran.
void show_wall(wall w, SDL_Surface *s) {
    SDL_BlitSurface(w.sprite, 0, s, &w.box);
}

// Affiche un fond d'écran à l'écran.
void show_wallpaper(SDL_Surface *wp, SDL_Surface *s) {
    SDL_BlitSurface(wp, 0, s, 0);
}

// Détermine les scores, et réinitialise la balle si un point vient
// d'être marqué (effet de bord ?).
void make_scores(wall &player01, wall &player02, ball &b) {
    if (b.x <= 0) {
	player02.score++;
	reset_ball(b);
    } else if (b.x+b.w >= SCREEN_WIDTH) {
	player01.score++;
	reset_ball(b);
    }
}

// Affiche les scores à l'écran.
void show_scores(TTF_Font *f, wall player01, wall player02, SDL_Surface *s) {
    SDL_Surface *score;
    SDL_Color white = { 255, 255, 255 };
    SDL_Rect pos;
    string message = "Score ";
    stringstream sstr;

    sstr << "Score : " << player01.score << "   " << player02.score;

    score = TTF_RenderText_Blended(f, sstr.str().c_str(), white);

    if (!score)
	cerr << "Surface de score non générée" << endl;

    pos.x = SCREEN_WIDTH/4;
    pos.y = 0;
    
    SDL_BlitSurface(score, 0, s, &pos);
    SDL_FreeSurface(score);
}

void show_finalscore(TTF_Font *f, SDL_Surface *s, bool player1win) {
    SDL_Surface *finalScore;
    SDL_Color color = { 0, 0, 0 };
    SDL_Rect pos;
    string message;

    if (player1win) {
        color.r = 255;
        message = "Joueur 1 gagne";
    } else {
        color.b = 255;
        message = "Joueur 2 gagne";
    }

    pos.x = 0;
    pos.y = SCREEN_HEIGHT/2;

    finalScore = TTF_RenderText_Blended(f, message.c_str(), color);

    SDL_BlitSurface(finalScore, 0, s, &pos);
    SDL_FreeSurface(finalScore);
}
    

// Fonction contenant la boucle de jeu principale
void play(void) {
    bool game = true;
    bool quit=false;
    SDL_Surface *screen;
    SDL_Surface *wallpaper;
    menu titleMenu;
    SDL_Event event;
    TTF_Font *pFont = 0;
    ball b;
    wall player01;
    wall player02;
    Uint8 *keystates = 0;

    SDL_Init(SDL_INIT_VIDEO); // VIDEO suffit amplement ...
    TTF_Init();
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,SDL_SWSURFACE);

    wallpaper = load_img("data/fond.bmp");

    init_menu(titleMenu);
    pFont = init_font();

    if (!pFont)
	cerr << "Police non correctement initialisée" << endl;
        
    init_wall(player01, "data/player01.bmp", WALL_MARGIN);
    init_wall(player02, "data/player02.bmp", SCREEN_WIDTH-WALL_WIDTH-WALL_MARGIN);
    initBall(b);

    while (!quit) {
        game = false;
        
        SDL_PollEvent(&event);
        show_menu(titleMenu, screen, event);
        if (play_selected(titleMenu, event) && event.button.button == SDL_BUTTON_LEFT)
            game = true;
        else if ( quit_selected(titleMenu, event) && event.button.button == SDL_BUTTON_LEFT)
            quit = true;
       
        SDL_Flip(screen);

	while(game && !quit)
	    {
            SDL_FillRect(screen,&screen->clip_rect, 
                         SDL_MapRGB(screen->format,255,255,255));
            
            show_wallpaper(wallpaper, screen);
            showBall(b, screen);
            show_wall(player01, screen);
            show_wall(player02, screen);
	    show_scores(pFont, player01, player02, screen);
            SDL_Flip(screen);
            
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT) // on quite le jeu
                    quit=true;
                if (event.key.keysym.sym == SDLK_ESCAPE) // retour au menu
		    game = false;
	    }
		     
            moveBall(b, player01, player02);
            
            keystates = SDL_GetKeyState(0);      
            move_wall(player01, keystates[SDLK_z], keystates[SDLK_s]);
            move_wall(player02, keystates[SDLK_UP], keystates[SDLK_DOWN]);

	    make_scores(player01, player02, b);

            if (player01.score >= SCORE_MAX || player02.score >= SCORE_MAX) {
                show_finalscore(pFont, screen, player01.score >= SCORE_MAX);
                SDL_Flip(screen);
                SDL_Delay(2000);
                reset_ball(b);
                reset_players(player01, player02);
                game = false;
            }
            
            SDL_Delay(5);
        }
    }

    free_font(pFont);
    free_ball(b);
    free_wall(player01);
    free_wall(player02);
    free_menu(titleMenu);
    SDL_FreeSurface(wallpaper);
    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();
}

// Fonction principale
int main(int argc, char* argv[])
{
    play();
    return EXIT_SUCCESS;
}

// ligne de compilation g++ -I/usr/include/SDL -L/usr/lib -lSDLmain -lSDL -lSDL_image -lSDL_ttf pong.cc -o pong //
// plus simple, `make' ... ;)
