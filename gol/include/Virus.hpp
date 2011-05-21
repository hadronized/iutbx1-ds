#ifndef VIRUS_HPP
#define VIRUS_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Randomizer.hpp>
#include <SFML/System/Vector2.hpp>

#include "Frame.hpp"

class Virus {
private :
    sf::Vector2f _position; // position a l'ecran du virus
    sf::Vector2f _direction; // direction (vecteur normalise) du virus
    float _freq; // frequence de changement de direction
    sf::Clock _clock; // horloge permettant de gerer la frequence de changement de direction
    int _incub; // permet de savoir quand on peut arreter l'incubation
    int _hp; // point de vie du virus

    static int const PADDING_SPAWN; // definit le padding de spawn des virus

    void fixPosition(int minx, int maxx, int miny, int maxy);
    
public :
    Virus(Frame const &limits);
    Virus(sf::Vector2f const &position);
    ~Virus(void);

    void changeDirection(void);
    void move(Frame const &limits);

    sf::Vector2f getPosition(void) const;
    sf::Vector2f getDirection(void) const;
    float getFreq(void) const;

    bool collideCell(bool alive, sf::Vector2f const &cellPos, sf::Vector2f const &cellDim, sf::Vector2f const &virusDim) const;

    void setNoIncub(void);
    void incub(void);
    int getIncub(void) const;

    void keepAlive(void); // le virus reste en vie (incubation)
    void degenerate(void); // le virus n'est pas en train d'incuber, il se degenere
    bool isDegenerated(void) const;
};

#endif // guard
