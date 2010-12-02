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

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int const SCREEN_W  = 640; // Largeur de la fenetre
int const SCREEN_H  = 400; // Hauteur de la fenetre
int const SCREEN_D  =  32; // Profondeur d'un pixel de l'ecran
int const BALL_D    =   6; // Dimension de la balle (BALL_D*BALL_D)
int const BALL_SX   =   2; // Vitesse de deplacement de la balle sur x
int const BALL_SY   =   2; // Vitesse de deplacement de la balle sur y
int const PLAYER_W  =  11; // Largeur d'un joueur
int const PLAYER_H  =  43; // Hauteur d'un joueur
int const PLAYER_SX =   4; // Vitesse de deplacement d'un joueur sur x
int const PLAYER_SY =   4; // Vitesse de deplacement d'un joueur sur y

typedef Uint8 key_state; // plus explicite pour gérer l'état des touches clavier

// Structure représentant une couleur RGB
struct color {
    char r;
    char g;
    char b;
};

// Structure représentant un object physique (une balle ou un joueur).
// Contrairement à ce que l'on pourrait croire, c'est bien plus qu'un
// sprite (la responsabilité de ce dernier étant simplement de stocker
// une image à l'écran et d'être pouvoir affiché à l'écran).
//
// Cette structure stocke un SDL_Rect (instancié sous `prop'), lequelle
// fournit des informations sur la position et les dimensions de l'objet.
// Elle fournit ensuite l'image contenu dans le sprite.
// Pour finir, elle contient deux entiers `sx' et `sy' dont la
// responsabilité est de gérer la vitesse sur deux axes de l'objet.
struct physic_object {
    SDL_Rect prop; // proprietes de l'objet (position (x;y), dimensions(w;h))
    int sx; // speed x : correspond à la vitesse sur l'axe x
    int sy; // speed y : correspond à la vitesse sur l'axe y
    SDL_Surface *pSprite; // image représentant l'objet dans le jeu
};

// Initialise la SDL et retourne un pointeur sur un SDL_Surface représentant
// l'écran.
SDL_Surface * init_sdl() {
    SDL_Surface *ps = 0;

    SDL_Init(SDL_INIT_VIDEO);
    ps = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_D, SDL_HWSURFACE
                                                                     #ifdef _FULLSCREEN
                                                                     | SDL_FULLSCREEN
                                                                     #endif
                                                                     );
    if (!ps) {
	std::cerr << "Echec de l'initialisation de la SDL" << std::endl;
        std::cerr << "Les raisons peuvent etre diverses, comme par exemple une mauvaise "
                  << "resolution si le mode fullscreen est actif" << std::endl;
    }
    return ps;
}

// Charge une image dans un SDL_Surface et retourne un pointeur sur ce dernier.
SDL_Surface * load_img(std::string const &fn) {
    SDL_Surface *ptmp = IMG_Load(fn.c_str());
    SDL_Surface *p = 0;

    if (!ptmp) {
	std::cerr << "Erreur: chargement de l'image " << fn << " échoué" << std::endl;
    } else {
	p = SDL_DisplayFormat(ptmp);
	if (!p)
	    std::cerr << "Erreur: conversion de l'image échouée" << std::endl;
	SDL_FreeSurface(ptmp);
    }
    
    return p;
}

// Charge une image dans un SDL_Surface et retourne un pointeur sur ce dernier.
// Cette fonction gère aussi un paramètre de color keying afin de rendre transparente
// une couleur passée comme paramètre (triplet).
SDL_Surface * load_img_key(std::string const &fn, int r, int g, int b) {
    SDL_Surface* optimizedImage;

    optimizedImage = load_img(fn);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b));
    return optimizedImage;
}

// Cette fonction permet de blit une surface sur une autre.
void blit_surface(SDL_Surface *from, SDL_Surface *to, SDL_Rect at) {
    SDL_BlitSurface(from, 0, to, &at); 
}

// Initialise les propriétés de l'objet passé en paramètre.
// Cette fonction retourne true si l'initialisation s'est bien déroulée,
// false sinon (et écrit dans ce dernier cas un message d'erreur).
bool init_phyo(physic_object &phyo, int x, int y, int w, int h, int sx, int sy, std::string const &fn) {
    phyo.prop.x = x;
    phyo.prop.y = y;
    phyo.prop.w = w;
    phyo.prop.h = h;
    phyo.sx = sx;
    phyo.sy = sy;
    phyo.pSprite = load_img_key(fn, 0, 255, 255);
    return phyo.pSprite != 0;
}

void free_phyo(physic_object &phyo) {
    if (phyo.pSprite) {
	SDL_FreeSurface(phyo.pSprite);
	phyo.pSprite = 0;
    }
}

// Détermine les collisions entre les deux murs (haut et bas) et la balle
// et corrige en l'occurence la trajectoire de cette dernière.
void walls_collide(physic_object &b) {
    if (b.prop.y <= 0 || b.prop.y+BALL_D >= SCREEN_H )
	b.sy *= -1;
}

// Gère les collisions avec les deux joueurs.
void players_collide(physic_object &b, physic_object &p1, physic_object &p2) {
    if ( b.prop.x <= p1.prop.x+p1.prop.w && b.prop.x+b.prop.w >= p1.prop.x && 
         b.prop.y+b.prop.h >= p1.prop.y && b.prop.y <= p1.prop.y+p1.prop.h ) { // joueur 1
        b.sx *= -1;
        b.prop.x = p1.prop.w;
    }
    else if ( b.prop.x+b.prop.w >= p2.prop.x && b.prop.x <= p2.prop.x+p2.prop.w && 
              b.prop.y+b.prop.h >= p2.prop.y && b.prop.y <= p2.prop.y+p2.prop.h ) { // joueur 2
	b.sx *= -1;
        b.prop.x = SCREEN_W-b.prop.w-p2.prop.w;
    }
}

// Déplace la balle et prévoit les collisions avec les murs et les raquettes.
void move_ball(physic_object &b, physic_object &r1, physic_object &r2) {
    b.prop.x += b.sx; // déplacement de la balle sur x
    b.prop.y += b.sy; // déplacement de la balle sur y

    walls_collide(b);
    players_collide(b, r1, r2);
}

bool player1won(physic_object b) {
    return b.prop.x+b.prop.w >= SCREEN_W;
}

bool player2won(physic_object b) {
    return b.prop.x <= 0;
}

// Déplace un joueur en fonction de la direction.
// Il est important de noter que si les deux touches 
// sont enfoncées, alors le joueur ne bouge plus.
// Cette fonction empêche de plus le joueur de sortir de l'écran.
void move_player(physic_object &p, bool up, bool down) {
    if ( (up && down) == false) { // si le joueur n'appuie pas sur les deux touches monter et descendre en meme temps
	if (up) { // si le joueur souhaite monter
	    p.prop.y -= p.sy;
	} else if (down) { // si le joueur souhaite descendre
	    p.prop.y += p.sy;
	}

        // Gestion sortie
        if (p.prop.y <= 0) {
            p.prop.y = 0;
        } else if (p.prop.y+p.prop.h >= SCREEN_H) {
            p.prop.y = SCREEN_H-p.prop.h;
        }
    }
}   

// Boucle de jeu principale
bool game_loop() {
    SDL_Surface *pScreen = 0;
    SDL_Surface *pWallp = 0;
    SDL_Event event;
    key_state *ks = 0;
    bool end = false;
    physic_object ball;
    physic_object player1;
    physic_object player2;
    
    pScreen = init_sdl();
    if (!pScreen)
	return false;

    bool test = true;
    // Initialisation des objets physiques (balle, joueur 1, joueur 2)
    test &= init_phyo(ball, (SCREEN_W-BALL_D)/2, (SCREEN_H-BALL_D)/2, BALL_D, BALL_D, BALL_SX, BALL_SY, "data/ball.bmp");
    test &= init_phyo(player1, 0, (SCREEN_H-PLAYER_H)/2, PLAYER_W, PLAYER_H, PLAYER_SX, PLAYER_SY, "data/player01.bmp");
    test &= init_phyo(player2, SCREEN_W-PLAYER_W, (SCREEN_H-PLAYER_H)/2, PLAYER_W, PLAYER_H, PLAYER_SX, PLAYER_SY, "data/player02.bmp");
    test &= static_cast<bool>((pWallp = load_img("data/fond.bmp")));
    
    if (!test) {
	std::cerr << "Initialisation sprites échouée" << std::endl;
	return 1;
    }

    

    while (!end) {
	while (SDL_PollEvent(&event)) {
	    switch (event.type) {
	        case SDL_QUIT :
		    end = true;
		    break;

	        case SDL_KEYUP :
		    switch (event.key.keysym.sym) {
		        case SDLK_ESCAPE :
			    end = true;
			    break;

                        default :;
		    }

	        default :;
	    }
	}

        ks = SDL_GetKeyState(0);

	move_ball(ball, player1, player2);
	move_player(player1, ks[SDLK_z], ks[SDLK_s]);
        move_player(player2, ks[SDLK_UP], ks[SDLK_DOWN]);

        if ( player1won(ball) ) {
            std::cout << "Le joueur 1 a gagné !" << std::endl;
            end = true;
        } else if ( player2won(ball) ) {
            std::cout << "Le joueur 2 a gagné !" << std::endl;
            end = true;
        }

	SDL_FillRect(pScreen, 0, SDL_MapRGBA(pScreen->format, 0, 0, 0, 255));
        blit_surface(pWallp, pScreen, SDL_Rect());
	blit_surface(ball.pSprite, pScreen, ball.prop);
	blit_surface(player1.pSprite, pScreen, player1.prop);
	blit_surface(player2.pSprite, pScreen, player2.prop);

	SDL_Flip(pScreen);
        SDL_Delay(5);
    }

    free_phyo(ball);
    free_phyo(player1);
    free_phyo(player2);
    SDL_Quit();

    return true;
}


int main() {
    std::cout << "Projet AP1S1 1 : Pong" << std::endl;
    std::cout << "Ludwig Raepsaet" << std::endl;
    std::cout << "Dimitri Sabadie" << std::endl;
    std::cout << "Licence GPL" << std::endl;
    std::cout << "Annee 2010" << std::endl;
    std::cout << std::endl;

    return game_loop();
}
