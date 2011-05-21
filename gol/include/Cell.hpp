#ifndef CELL_HPP
#define CELL_HPP

class Cell {
private :
    bool _alive;

public:
    /**
     * \param  alive renseigne sur l'état de la cellule (en vie, ou pas)
     */
     Cell (bool alive = false );
    ~Cell();

    /** Permet de marquer la cellule comme vivante
     */
    void bear();
    /** Permet de marquer la cellule comme morte
     */
    void die();
    /**
     * \return true si la cellule est en vie, false sinon
     */
    bool isAlive ( ) const;
};

#endif // CELL_HPP
