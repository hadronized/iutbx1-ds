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

#include <iostream> // uniquement pour tests
#include "algorithm.h"
#include "array.h"

using namespace std;

bool array_insert(int x, int *a, int &n, int nmax) {
    int i = 0;

    if (n >= nmax)
        return false;
    while (i < n) {
        if (a[i] == x) { // doublon, on refuse
            return false;
        } if (a[i] > x) {
            for (int y = n; y > i; --y)
                int_swap(a[y], a[y-1]);
            a[i] = x;
            ++n;
            return true;
        } else {
            ++i;
        }
    }

    a[n] = x;
    ++n;
    return true;
}

#include "matrix.h"
void show_array(int *a, int n) {
    for (int i = 0; i < n; ++i)
        cout << '(' << a[i]%MATRIX_WIDTH << ';' << a[i]/MATRIX_WIDTH << ')' << endl;
}
