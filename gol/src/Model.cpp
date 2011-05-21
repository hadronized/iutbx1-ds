#include "Model.hpp"
#include <fstream>
#include <string.h>
#include <iostream> // test

using namespace std;


/**
 * @param  row nombre de lignes de la matrice de cellules intiale
 * @param  col nombre de colonnes de la matrice de cellules initiale
 */
GameModel::GameModel(int row, int col) :
    _minAlive(2),
    _maxAlive(3),
    _minDead(3),
    _maxDead(3) {
    setRow(row);
    setCol(col);
}

GameModel::~GameModel() {
}

/**
 * @param  row nouveau nombre de ligne de la matrice à prendre en compte
 */
void GameModel::setRow(int row) {
    /* ici, on redimensionne notre matrice en fonction du nombre de lignes souhaitees
       si des lignes sont supprimees apres le redimensionnement, elles sont definitivement
       perdues */
    _cells.resize(row+2);
    _nextCells.resize(row+2);
    for (int i = 0; i < _cells.size(); ++i) {
        _cells[i].resize(getCol()+2);
        _nextCells[i].resize(getCol()+2);
    }
}

/**
 * @param  col nouveau nombre de colonnes de la matrice de cellules à prendre en
 * compte
 */
void GameModel::setCol(int col) {
    /* ici, on redimensionne chaque ligne de notre matrice en fonction du nombre de colonnes souhaitees
       si des colonnes sont supprimees apres le redimensionnement, elles sont definitivement
       perdues */
    for (int i = 0; i < _cells.size(); ++i) {
        _cells[i].resize(col+2);
        _nextCells[i].resize(col+2);
    }
}

/**
 * @return le nombre de lignes
 */
int GameModel::getRow() const {
    return _cells.size()-2;
}

/**
 * @return le nombre de colonnes
 */
int GameModel::getCol() const {
    /* si une matrice est vide (pas de lignes), elle n'a evidemment pas de colonnes
       partant de ce principe, si une matrice a au moins une ligne, on a accès
       à son nombre de colonnes a travers chaque sous std::vector qui la compose
       (chaque sous std::vector representant les lignes de la matrice)
       on prendra donc la longueur de la premiere ligne si elle existe, sinon 0
     */

    return _cells.empty() ? 0 : _cells[0].size()-2;
}

/**
 * Calcule le nombre de voisines vivantes d'une cellule a un endroit precis du plateau de jeu
 * @param i indice de la cellule dont on veut connaitre le nombre de voisines en vie
 * @param j indice de la cellule dont on veut connaitre le nombre de voisines en vie
 * @return le nombre de voisines vivantes de la cellule
 */
int GameModel::check8NeighAlive(int i, int j) const {
    int nb = 0;

    for (int p = 0; p <= 2; p += 2) {
	for (int k = 0; k < 3; ++k)
	    nb += _cells[i-1+p][j-1+k].isAlive(); // hack
	nb += _cells[i][j-1+p].isAlive(); // hack
    }

    return nb;
}

/**
 * @return une reference sur une matrice constante des cellules a l'etape actuelle de la simulation
 */
matrix_t const & GameModel::getCells() const {
    return _cells;
}

/**
 * Permet de generer l'etape suivante de la simulation
 * Une solution plus elegante consiste a utiliser deux matrices ping/pong
 */
int GameModel::next() {
    int neigh = 0;
    int t = 0;

    for (int i = 1; i < _cells.size()-1; ++i) {
        for (int j = 1; j < _cells[0].size()-1; ++j) {
            neigh = check8NeighAlive(i, j);
            if (_cells[i][j].isAlive()) { // la cellule est vivante
		if (neigh >= _minAlive & neigh <= _maxAlive) {
		    t++;
                    _nextCells[i][j] = _cells[i][j];
		} else {
		    _nextCells[i][j].die();
		}
	    } else { // la cellule est morte
                if (neigh >= _minDead && neigh <= _maxDead) { // la cellule nait
		    t++;
                    _nextCells[i][j].bear();
		} else {
                    _nextCells[i][j].die();
                }
            }
        }
    }

    // mise a jour des cellules pour l'etape suivante
    // technique du ping/pong a implementer d'urgence !
    for (int i = 0; i < _cells.size(); ++i) {
	for (int j = 0; j < _cells[0].size(); ++j) {
            _cells[i][j] = _nextCells[i][j];
	}
    }

    return t;
}

bool GameModel::isAlive(int i, int j) const {
    return _cells[i+1][j+1].isAlive();
}

/**
 * @return true si il reste encore au moins une cellule vivante, false sinon
 */
bool GameModel::stillAlive() const {
    for (std::vector< std::vector<Cell> >::const_iterator row = _cells.begin(); row != _cells.end(); ++row) {
        for (std::vector<Cell>::const_iterator col = row->begin(); col != row->end(); ++col) {
            if (col->isAlive()) // il reste au moins une cellule en vie dans le tableau
                return true;
        }
    }

    // on a parcouru tout le tableau de jeu sans trouver une seule cellule encore en vie
    return false;
}

/**
 * Permet de faire naitre une cellule a un endroit precis du plateau de jeu
 * @param i indice de la ligne de la cellule a faire naitre
 * @param j indice de la colonne de la cellule a faire neitre
 */
void GameModel::makeAlive(int i, int j) {
    _cells[i+1][j+1].bear();
}

/**
 * Permet de tuer une cellule a un endroit precis du plateau de jeu
 * @param i indice de la ligne de la cellule a tuer
 * @param j indice de la colonne de la cellule a tuer
 */
void GameModel::kill(int i, int j) {
  _cells[i+1][j+1].die();
}

void GameModel::setMinAlive(int v) {
    _minAlive = v;
}

void GameModel::setMaxAlive(int v) {
    _maxAlive = v;
}

void GameModel::setMinDead(int v) {
    _minDead = v;
}

void GameModel::setMaxDead(int v) {
    _maxDead = v;
}

int GameModel::getMinAlive() const {
    return _minAlive;
}

int GameModel::getMaxAlive() const {
    return _maxAlive;
}

int GameModel::getMinDead() const {
    return _minDead;
}

int GameModel::getMaxDead() const {
    return _maxDead;
}

void GameModel::save()
{
    //push_back( Virus(_frameBG, _virus_sprite.GetSize().x) );
    ofstream f("save.txt");
    if (!f.is_open())
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    else{
        f<<getRow();
        f<<" ";
        f<<getCol();
        f<<endl;
        for (int i = 0; i < getRow(); i++ ) {
            for (int j = 0; j < getCol(); j++ )
                f << isAlive(i,j);
            f<<endl;
        }
    }
    f.close();
}

void GameModel::load()
{
    char stream;
    int col =0;
    int row = 0;
    ifstream f ("save.txt", ios::in);
    if (!f.is_open())
	std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    else
    {
        f >> row >> col;
        setRow(row);
        setCol(col);

        f.ignore(1024, '\n');
        for (int i = 0; i < getRow(); i++ ) {
            for (int j = 0; j < getCol(); j++ ) {
                f.get(stream);
                if (stream == '1')
                    makeAlive(i,j);
                else
                    kill(i,j);
            }
		
            f.ignore(1024, '\n');
        }
    }
    f.close();
}
