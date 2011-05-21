#include <cassert>
#include "Slider.hpp"

Slider::Listener::Listener() {
}

Slider::Listener::~Listener() {
}



Slider::Slider(Frame frame, sf::Sprite spritebg, sf::Sprite spritecurs, int min, int max, int value, Slider::Listener *pListener) :
    WidgetBase(frame, spritebg),
    _min(min),
    _max(max),
    _value(value),
    _cursor(spritecurs),
    _pListener(pListener) {
    assert(min < max);
    maj();
}

Slider::~Slider() {
}

void Slider::maj() {
    WidgetBase::maj(); // mise a jour du background
    
    /* Mise a jour du curseur ici. Le principe est simple : _min nous donne
       la position la plus a gauche du curseur. Donc quand _value == _min,
       la position du curseur est (PX, PY). Lorsque _value == _max, le curseur
       est tout a droite. Il faut diviser la longueur du slider par la
       difference entre le max et le min pour avoir le nombre de pixels qui
       separent chaque "trait" du slider
     */
    float d = _max - _min;
    float w = _frame.getWidth() / d; // longueur d'un segment de slider

    Frame f = Frame( _frame.getPX() + (_value-_min)*w - _frame.getWidth()/30, _frame.getPY(), _frame.getWidth()/15, _frame.getHeight() );
    _cursor.Resize( f.getWidth(), f.getHeight() );
    _cursor.SetPosition( f.getPX(), f.getPY() );
}

bool Slider::relayEvents(sf::Event const &event, sf::Input const &input) {
    if (WidgetBase::relayEvents(event, input)) { // evenement capture : traitement
	if (input.IsMouseButtonDown(sf::Mouse::Left)) {
	    // on doit deplacer le curseur en consequence et modifier la valeur du slider
	    float px = input.GetMouseX();
	    float d = _max - _min;
	    float w = _frame.getWidth() / d;
	    int value = (px - _frame.getPX() + w/2) / w + _min; // valeur pointee par le curseur
	    setValue(value);

            // notification
            if (_pListener)
                _pListener->notifyChangedValue(*this);
	}
	return true;
    }

    return false;
}

void Slider::draw(sf::RenderWindow &window) const {
    WidgetBase::draw(window);
    window.Draw(_cursor);
}

void Slider::setValue(int value) {
    _value = value;

    // clamp
    if (_value < _min) _value = _min;
    else if (_value > _max) _value = _max;

    maj(); // un peu bourrin
}

int Slider::getValue() const {
    return _value;
}

int Slider::getMin() const {
    return _min;
}

int Slider::getMax() const {
    return _max;
}
