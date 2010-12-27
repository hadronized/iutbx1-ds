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

#include <iostream> // pour tests
#include "gameplay.h"
#include "array.h"
#include "score.h"
#include "temps.h"

using namespace std;

void init_player(player &p) {
    p.score = 0;
    p.action = 0;
    p.reanim = 0;
}

bool try_swap(gameboard &gb, diamond &a, diamond &b, SDL_Surface *ps) {
    bool success = false;
    int vx;
    int vy;
    
    if ( is_near(a, b) ) { // tentative possible
        vx = (b.box.x-a.box.x)/DIAMOND_SIZE;
        vy = (b.box.y-a.box.y)/DIAMOND_SIZE;

        draw_diamond_swap(gb, a, b, vx, vy, ps);
        diamond_swap(a, b);

	if ( check_explode(gb) ) // si il y a eu au moins une explosion, peut-être il faudrait optimiser ça
            success = true;
        else { // si aucune explosion generee, on reechange les diamants
            draw_diamond_swap(gb, a, b, vx, vy, ps);
            diamond_swap(a, b);
        }
    } 
    
    return success;
}

bool check_explode(gameboard &gb) {
    int index;
    diamond tmp;
    diamond_type root;
    int count = 1;

    gb.nb_expl = 0;
    
    // test horizontal
    for (int j = 0; j < gb.col; ++j) {
        root = -1; // reinitialisation diamant en debut de ligne
        for (int i = 0; i < gb.row; ++i) {
            index = index_2D1D(i, j, gb.row);
            tmp = gb.dmds[index];

            if (tmp.type == root) {
                ++count;
            } else {
                if (count >= 3) {
                    --index;
                    for (int y = 0; y < count; ++y)
                        array_insert(index-y, gb.expl, gb.nb_expl, gb.col*gb.row);
                }
                root = tmp.type;
                count = 1;
            }
        }
    }

    if (count >= 3) {
        for (int y = 0; y < count; ++y)
            array_insert(index-y, gb.expl, gb.nb_expl, gb.col*gb.row);
    }
    
    // test vertical
    count = 1;
    for (int i = 0; i < gb.row; ++i) {
        root = -1;
        for (int j = 0; j < gb.col; ++j) {
            index = index_2D1D(i, j, gb.row);
            tmp = gb.dmds[index];

            if (tmp.type == root) {
                ++count;
            } else {
                if (count >= 3) {
                    if (j == 0) // j-1 risque de ne pas etre apprecie ici, d'ou ce test ;)
                        index = index_2D1D(i-1, gb.col-1, gb.row);
                    else
                        index = index_2D1D(i, j-1, gb.row);
                    for (int y = 0; y < count; ++y)
                        array_insert(index-y*gb.row, gb.expl, gb.nb_expl, gb.col*gb.row);
                }
                root = tmp.type;
                count = 1;
            }
        }
    }

    if (count >= 3) {
        for (int y = 0; y < count; ++y)
            array_insert(index-y*gb.row, gb.expl, gb.nb_expl, gb.col*gb.row);
    }

    return gb.nb_expl != 0;
}

void explode(gameboard &gb, SDL_Surface *ps) {
    SDL_Rect pos;
    SDL_Rect sub;
    int tmpx, tmpy;

    sub.y = 0;
    sub.w = DIAMOND_SIZE;
    sub.h = DIAMOND_SIZE;

    for (int y = 0; y < 9; ++y) { // attention constante magique moche : 9, car 9 frames par explosion ...
        sub.x = y*DIAMOND_SIZE;
        for (int i = 0; i < gb.nb_expl; ++i) {
            index_1D2D(gb.expl[i], tmpx, tmpy, gb.row);
            
            pos.x = tmpx*DIAMOND_SIZE;
            pos.y = tmpy*DIAMOND_SIZE;

            SDL_BlitSurface(gb.explode, &sub, ps, &pos);
        }
        
        SDL_Flip(ps);
        SDL_Delay(80);
    }
}

void get_down(gameboard &gb, SDL_Surface *ps) {
    int x, y;
    diamond *pd;

    for (int i = 0; i < gb.nb_expl; ++i) {
        index_1D2D(gb.expl[i], x, y, gb.row);
        //query_diamond(gb, x, y).box.y = -DIAMOND_SIZE;
        while (y > 0) {
            diamond_swap(query_diamond(gb, x, y), query_diamond(gb, x, y-1));
            //sdlrect_swap(query_diamond(gb, x, y).box, query_diamond(gb, x, y-1).box);
            --y;
        }
        
        pd = &query_diamond(gb, x, 0);
        change_diamond_type(*pd, pd->type, pd->type);
    }

    //draw_getdown(gb, ps);
}

bool check_pattern_h1(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif h11
    // deuxieme passage dans la boucle : on teste le motif h12
    for (int symx = 0; symx < 2; ++symx) { // symetrie sur l'axe x
        a = query_diamond(gb, i, j+symx);
        b = query_diamond(gb, i+1, j+1-symx);
        c = query_diamond(gb, i+2, j+symx);

        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+1, j+1-symx, gb.row);
            return true;
        }
    }

    return false;
}

bool check_pattern_h2(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif h21
    // deuxieme passage dans la boucle : on teste le motif h22
    for (int symx = 0; symx < 2; ++symx) { // symetrie sur l'axe x
        a = query_diamond(gb, i, j+symx);
        b = query_diamond(gb, i+1, j+symx);
        c = query_diamond(gb, i+2, j+1-symx);
            
        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+2, j+1-symx, gb.row);
            return true;
        }
    }

    // premier passage dans la boucle : on teste le motif h23
    // deuxieme passage dans la boucle : on teste le motif h24
    for (int symx = 0; symx < 2; ++symx) { // symetrie sur l'axe x
        a = query_diamond(gb, i, j+1-symx);
        b = query_diamond(gb, i+1, j+symx);
        c = query_diamond(gb, i+2, j+symx);
            
        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i, j+1-symx, gb.row);
            return true;
        }
    }

    return false;
}

bool check_pattern_h3(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif h31
    // deuxieme passage dans la boucle : on teste le motif h32
    a = query_diamond(gb, i, j);
    b = query_diamond(gb, i+3, j);
    for (int symy = 0; symy < 2; ++symy) { // symetrie sur l'axe y
        c = query_diamond(gb, i+2-symy, j);

        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+3*symy, j, gb.row);
            return true;
        }
    }

    return false;
}

bool check_pattern_v1(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif v11
    // deuxieme passage dans la boucle : on teste le motif v12
    for (int symy = 0; symy < 2; ++symy) { // symetrie sur l'axe y
        a = query_diamond(gb, i+symy, j);
        b = query_diamond(gb, i+1-symy, j+1);
        c = query_diamond(gb, i+symy, j+2);

        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+1-symy, j+1, gb.row);
            return true;
        }
    }

    return false;
}

bool check_pattern_v2(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif v21
    // deuxieme passage dans la boucle : on teste le motif v22
    for (int symy = 0; symy < 2; ++symy) { // symetrie sur l'axe y
        a = query_diamond(gb, i+symy, j);
        b = query_diamond(gb, i+symy, j+1);
        c = query_diamond(gb, i+1-symy, j+2);
            
        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+1-symy, j+2, gb.row);
            return true;
        }
    }

    // premier passage dans la boucle : on teste le motif v23
    // deuxieme passage dans la boucle : on teste le motif v24
    for (int symy = 0; symy < 2; ++symy) { // symetrie sur l'axe y
        a = query_diamond(gb, i+1-symy, j);
        b = query_diamond(gb, i+symy, j+1);
        c = query_diamond(gb, i+symy, j+2);
            
        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i+1-symy, j, gb.row);
            return true;
        }
    }

    return false;
}

bool check_pattern_v3(gameboard &gb, int i, int j) {
    diamond a, b, c;

    // premier passage dans la boucle : on teste le motif v31
    // deuxieme passage dans la boucle : on teste le motif v32
    a = query_diamond(gb, i, j);
    b = query_diamond(gb, i, j+3);
    for (int symx = 0; symx < 2; ++symx) { // symetrie sur l'axe x
        c = query_diamond(gb, i, j+2-symx);
            
        if (equal(a, b, c)) {
            gb.index_sol = index_2D1D(i, j+3*symx, gb.row);
            return true;
        }
    }

    return false;
}

bool check_solution(gameboard &gb) {
    for (int j = 0; j < gb.col; ++j) {
        for (int i = 0; i < gb.row-2; ++i) {
            if (j < gb.col-1) {
                if (check_pattern_h1(gb, i, j) || check_pattern_h2(gb, i, j))
                    return true;
            } 
            if (i < gb.row-3) {
                if (check_pattern_h3(gb, i, j))
                    return true;
            }
        }
    }

    for (int i = 0; i < gb.row; ++i) {
        for (int j = 0; j < gb.col-2; ++j) {
            if (i < gb.row-1) {
                if (check_pattern_v1(gb, i, j) || check_pattern_v2(gb, i, j))
                    return true;
            }
            if (j < gb.col-3) {
                if (check_pattern_h3(gb, i, j))
                    return true;
            }
        }
    }

    return false;
}

void solo_loop(SDL_Surface *ps) {
    SDL_Event event;
    bool quit = false;
    gameboard gb;
    diamond *pSelected = 0;
    player user;
    int comboScore;
    Uint32 t0;
    int temps; 	 
    int temps_restant;
    int tps;
    
    TTF_Font *pFont = 0;
    TTF_Init();
    pFont = init_font();
    if (!pFont)
        cerr << "Police non initialisée" << endl;

    temps = 180;
    tps = time(0);
	
    temps_restant = temps - ( time(0) - tps);

    load_theme("themes/fractal_cosmos/", gb);
    init_gameboard(gb, 8, 8);
    init_player(user);
    
    if (check_solution(gb)) {
        t0 = SDL_GetTicks();

        while (!quit) {
            SDL_FillRect(ps, 0, SDL_MapRGB(ps->format, 255, 255, 255));
            temps_restant = temps - ( time(0) - tps);
            
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    quit = true; // on quitte le jeu -> retour au menu principal
                if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                    if (cursor_in_grid(event, gb)) {
                        if (!pSelected) { // si aucun diamant n'était selectionné prealablement ...
                            pSelected = &query_diamond(gb, event.motion.x/DIAMOND_SIZE, event.motion.y/DIAMOND_SIZE);
                            pSelected->sub.y = DIAMOND_SIZE;
                        } else { // sinon, c'est que l'on en selectionne un deuxième -> on tente donc un echange
                            pSelected->sub.y = 0;
                            if ( try_swap(gb, *pSelected, query_diamond(gb, event.motion.x/DIAMOND_SIZE, event.motion.y/DIAMOND_SIZE), ps) ) {
                                comboScore = 1;
                                do {
                                    user.score += gb.nb_expl * comboScore;
                                    user.reanim = user.action = user.score;
                                    ++comboScore;
                                    
                                    show_gameboard(gb, ps);
                                    scores(pFont,ps,user.score);
                                    affiche_temps(pFont,ps,temps_restant);

                                    explode(gb, ps);
                                    get_down(gb, ps);
                                } while ( check_explode(gb));

                                if (user.action >= 10) { // a modifier en fonction de la difficulte choisie
                                    // lancer le bonus action ici
                                    cout << "ACTION !" << endl;
                                    user.action = 0;
                                }

                                t0 = SDL_GetTicks();

                                if (check_solution(gb)) { // il reste des solutions
                                    ;
                                } else { // plus de solution
                                    // verifier la presence de bonus reanimation
                                    // si pas de bonus
                                    game_over(gb, pFont, ps);
                                    quit = true;
                                }
                            }
			
                            pSelected = 0;
                        }
                    }
                }
            }
	
            if (SDL_GetTicks() - t0 >= MS_BEFORE_SOLUTION) {
                draw_solution(gb, ps);
                t0 = SDL_GetTicks();
            }
            
            show_gameboard(gb, ps);
            scores(pFont,ps,user.score);
            affiche_temps(pFont,ps,temps_restant);

            SDL_Flip(ps);
        }
    }

    in_top_ten_solo(pFont, ps, user.score);

    free_theme(gb);
    free_font(pFont);
}

bool cursor_in_grid(SDL_Event e, gameboard const &gb) {
    return (e.motion.x >= 0 && e.motion.x <= gb.row*DIAMOND_SIZE)
        && (e.motion.y >= 0 && e.motion.y <= gb.col*DIAMOND_SIZE);
}



