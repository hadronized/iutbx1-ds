#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Widget.hpp"

class Slider : public WidgetBase {
public :
    class Listener {
    public :
	Listener(void);
	~Listener(void);
	
	// signaux ici
	virtual void notifyChangedValue(Slider &sender) = 0;
    };

private:
    int _min;
    int _max;
    int _value;
    sf::Sprite _cursor;
    Listener *_pListener;

public:
    Slider(Frame frame, sf::Sprite spritebg, sf::Sprite spritecurs, int min, int max, int value, Listener *pListener = 0);
    ~Slider();
    
    void maj(void);

    bool relayEvents(sf::Event const &event, sf::Input const &input);
    void draw(sf::RenderWindow &event) const;

    void setValue(int value);
    int getValue(void) const;

    int getMin(void) const;
    int getMax(void) const;
};

#endif
