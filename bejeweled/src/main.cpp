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

#include <iostream>
#include <cstdlib>
#include <string>
#include "gameplay.h"
#include "menu.h"
#include <cmath>

using namespace std;

string const VERSION  = "0.1a";
string const AUTHORS  = "Dimitri Sabadie <dimitri.sabadie@etu.u-bordeaux1.fr>\n"
                        "Ludwig Raepsaet <ludwig.raepsaet@etu.u-bordeaux1.fr>";
string const COPYING  = "GPL";
int const YEAR        = 2010;

int main() {
    int rcode = 0;
    SDL_Surface *ps = 0;

    cout << SCREEN_TITLE << " version " << VERSION << endl;
    cout << AUTHORS << endl;
    cout << "Licence : " << COPYING << endl;
    cout << "Annee   : " << YEAR << endl;
    cout << endl;

    srand(time(0)); // initialisation randomizer

    if (init_gui()) {
	ps = create_screen();
	if (ps)
	    menu_loop(ps);	
	    rcode = solo_loop(ps);

    }
    
    quit_gui();
    
    return rcode;
}
