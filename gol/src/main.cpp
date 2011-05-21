#include <cstdlib> // pour srand() et time()
#include <iostream>
#include "Model.hpp"
#include "View.hpp"

using namespace std;

const int SCREEN_WIDTH =  800;
const int SCREEN_HEIGHT = 600;

int main() {
    cout << "Projet universitaire IUT Bordeaux 1 AP 2 : Game Of Life" << endl;
    cout << "Developpe par :" << endl;
    cout << " - Dimitri Sabadie" << endl;
    cout << " - Khalif Lahbibi" << endl;
    cout << "Licence GPL" << endl;
    cout << "Annee 2011" << endl;

    srand(time(0));

    GameModel *model = new GameModel(SCREEN_HEIGHT/10, SCREEN_HEIGHT/10);
    GameView *view = new GameView(SCREEN_WIDTH, SCREEN_HEIGHT, model);
  
    while (view->treatEvents()) {
        view->game();
    }
  
    delete view;
    delete model;

    return 0;
}
