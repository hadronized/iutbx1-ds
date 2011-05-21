#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics.hpp>

class Frame{
protected:
    float _px;
    float _py;
    float _width;
    float _height;

public:
    Frame(float px, float py, float width, float height);
    ~Frame();
    float getPX() const;
    float getPY() const;
    float getWidth() const;
    float getHeight() const;
    void setPX(float px);
    void setPY(float py);
    void setWidth(float width);
    void setHeight(float height);

    bool focused(const sf::Input &input) const; // verifie si la souris est dans le frame
    bool focused(const sf::Event &event) const; // verifie si la souris est dans le frame
};

#endif
