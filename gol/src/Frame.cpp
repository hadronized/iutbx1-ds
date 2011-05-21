#include "Frame.hpp"

Frame::Frame(float px, float py, float width, float height) :
    _px(px),
    _py(py),
    _width(width),
    _height(height) {
}

Frame::~Frame(){};

float Frame::getPX() const{
    return _px;
}

float Frame::getPY() const{
    return _py;
}

float Frame::getWidth() const {
    return _width;
}

float Frame::getHeight() const {
    return _height;
}

void Frame::setPX(float px) {
    _px = px;
}

void Frame::setPY(float py) {
    _py = py;
}

void Frame::setWidth(float width) {
    _width = width;
}

void Frame::setHeight(float height) {
    _height = height;
}

bool Frame::focused(const sf::Input &input) const {
    float mx = input.GetMouseX();
    float my = input.GetMouseY();

    if ((mx >= _px && mx <= _px+_width) && (my >= _py && my <= _py+_height))
        return true;
    return false;
}

bool Frame::focused(const sf::Event &event) const {
    float mx = event.MouseMove.X;
    float my = event.MouseMove.Y;

    if ((mx >= _px && mx <= _px+_width) && (my >= _py && my <= _py+_height))
        return true;
    return false;
}
