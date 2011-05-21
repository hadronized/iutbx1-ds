#include "Cell.hpp"

Cell::Cell(bool alive) : _alive(alive) {
}

Cell::~Cell() {
}


void Cell::bear() {
    _alive = true;
}

void Cell::die() {
    _alive = false;
}


bool Cell::isAlive() const {
    return _alive;
}
