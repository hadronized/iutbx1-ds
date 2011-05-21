#include <cmath>
#include <cstdlib> // pour rand()
#include "Virus.hpp"

int const Virus::PADDING_SPAWN = 0.f;

Virus::Virus(Frame const &limits) :
    _incub(0),
    _hp(100) {
    int minx = limits.getPX() + PADDING_SPAWN;
    int maxx = limits.getPX() + limits.getWidth() - PADDING_SPAWN;
    int miny = limits.getPY() + PADDING_SPAWN;
    int maxy = limits.getPY() + limits.getHeight() - PADDING_SPAWN;

    _position.x = rand() % (maxx - minx + 1) + minx;
    _position.y = rand() % (maxy - miny + 1) + miny;

    changeDirection();
}

Virus::Virus(sf::Vector2f const &position) :
    _incub(0),
    _hp(50)  {
    _position = position;
    changeDirection();
}

Virus::~Virus() {
}

void Virus::fixPosition(int minx, int maxx, int miny, int maxy) {
    if (_position.x <= minx)
        _position.x = minx;
    else if (_position.x >= maxx)
        _position.x = maxx-1;
    if (_position.y <= miny)
        _position.y = miny;
    else if (_position.y >= maxy)
        _position.y = maxy-1;
}

void Virus::changeDirection() {
    /* La boucle ci dessous permet d'eviter d'avoir une vilaine division par 0.
       En theorie, on ne devrait rentrer qu'une seule fois dans cette boucle, le cas
       _position == _direction etant vraiment invraisemblable, mais on ne sait jamais ;)
    */
    do {
        _direction.x = 1.f * (rand() % 2000 - 1000) / 1000;
        _direction.y = 1.f * (rand() % 2000 - 1000) / 1000;
    } while (_direction == _position);

    //_direction -= _position; // creation de notre vecteur direction
    _direction /= std::sqrt(_direction.x*_direction.x + _direction.y*_direction.y);
    // choquant de voir que la normalisation n'est pas core-feature dans la sfml ...

    // comportement fun qui permet d'avoir des virus au comportement completement aleatoire ! :)
    _freq = 1.f * (rand() % 100 + 1) / 100;
}
    
void Virus::move(Frame const &limits) {
    int minx = limits.getPX() + PADDING_SPAWN;
    int maxx = limits.getPX() + limits.getWidth() - PADDING_SPAWN;
    int miny = limits.getPY() + PADDING_SPAWN;
    int maxy = limits.getPY() + limits.getHeight() - PADDING_SPAWN;

    _position += _direction;
    fixPosition(minx, maxx, miny, maxy);

    if (_clock.GetElapsedTime() >= _freq) {
	changeDirection();
	_clock.Reset();
    }
}

sf::Vector2f Virus::getPosition() const {
    return _position;
}

sf::Vector2f Virus::getDirection() const {
    return _direction;
}

float Virus::getFreq() const {
    return _freq;
}

bool Virus::collideCell(bool alive, sf::Vector2f const &cellPos, sf::Vector2f const &cellDim, sf::Vector2f const &virusDim) const {
    if (!alive)
        return false;

    sf::Vector2f virusCenter = _position + virusDim/2.f;
    sf::Vector2f cellCenter = cellPos + cellDim/2.f;
    sf::Vector2f diff = virusCenter - cellCenter;

    return std::sqrt(diff.x*diff.x + diff.y*diff.y) <= (std::min(cellDim.x, cellDim.y)/2)*1.5f; 
}

void Virus::setNoIncub() {
    _incub = 0;
}

void Virus::incub() {
    _incub++;
}

int Virus::getIncub() const {
    return _incub;
}

void Virus::keepAlive() {
    _hp = 100;
}

void Virus::degenerate() {
    _hp--;
}

bool Virus::isDegenerated() const {
    return _hp <= 0;
}
