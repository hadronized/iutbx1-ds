#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "Cell.hpp"
#include "Virus.hpp"

typedef std::vector<Cell> row_t;
typedef std::vector<row_t> matrix_t;

class GameModel {
private :
    matrix_t _cells; // matrice de cellules
    matrix_t _nextCells; // matrice de cellules

    int _minAlive, _maxAlive;
    int _minDead, _maxDead;

    /**
     * @brief Calcule le nombre de voisines vivantes d'une cellule a un endroit precis du plateau de jeu
     * @param i indice de la cellule dont on veut connaitre le nombre de voisines en vie
     * @param j indice de la cellule dont on veut connaitre le nombre de voisines en vie
     * @return le nombre de voisines vivantes de la cellule
     */
    int check8NeighAlive(int i, int j) const;

public :
    /**
     * @param  row nombre de lignes de la matrice de cellules intiale
     * @param  col nombre de colonnes de la matrice de cellules initiale
     */
    GameModel(int row = 20, int col = 20);
    ~GameModel();
    
    /**
     * @param  row nouveau nombre de ligne de la matrice de cellules à prendre en compte
     */
    void setRow(int row);
    /**
     * @param  col nouveau nombre de colonnes de la matrice de cellules à prendre en
     * compte
     */
    void setCol(int col);
    /**
     * @return le nombre de lignes
     */
    int getRow() const;
    /**
     * @return le nombre de colonnes
     */
    int getCol() const;
    /**
     * @return une reference sur une matrice constante des cellules à l'etape actuelle de la simulation
     */
    matrix_t const & getCells() const;
    /**
     * @brief Permet de generer l'etape suivante de la simulation. Retourne le nombre de cellules vivantes.
     */
    int next();
    /**
     * @return true si la cellule concernée est vivante, false sinon
     */
    bool isAlive(int i, int j) const;
    /**
     * @return true si il reste encore au moins une cellule vivante, false sinon
     */
    bool stillAlive() const;
    /**
     * @brief Permet de faire naitre une cellule a un endroit precis du plateau de jeu
     * @param i indice de la ligne de la cellule a faire naitre
     * @param j indice de la colonne de la cellule a faire neitre
     */
    void makeAlive(int i, int j);
    /**
     * @brief Permet de tuer une cellule a un endroit precis du plateau de jeu
     * @param i indice de la ligne de la cellule a tuer
     * @param j indice de la colonne de la cellule a tuer
     */
    void kill(int i, int j);

    void setMinAlive(int v);
    void setMaxAlive(int v);
    void setMinDead(int v);
    void setMaxDead(int v);

    int getMinAlive(void) const;
    int getMaxAlive(void) const;
    int getMinDead(void) const;
    int getMaxDead(void) const;
    void save();
    void load();
};

#endif // MODEL_HPP
