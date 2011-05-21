#ifndef INTRO_HPP
#define INTRO_HPP

#include <SFML/Graphics.hpp>

class Introduction {
private :
    sf::Image _back_image;
    sf::Sprite _back_sprite;

public :
    Introduction(void);
    ~Introduction(void);

    void draw(sf::RenderWindow &window, sf::Image image, sf::Sprite sprite);
};

#endif // guard
