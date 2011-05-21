#include <sstream>
#include "Text.hpp"

using std::stringstream;

Text::Text(Frame frame, std::string const &text) :
  WidgetBase(frame, sf::Sprite()),
  _text(text) {
  _text.SetSize(20);
  _text.SetColor(sf::Color::Black);
  maj();

  }


Text::~Text() {
}


void Text::maj() {
    sf::FloatRect rect;
    _text.SetSize(_frame.getHeight());
    rect = _text.GetRect();
    _text.SetX(_frame.getPX() + (_frame.getWidth() - rect.GetWidth())/2);
    _text.SetY(_frame.getPY());
}

void Text::setText(std::string const &text) {
  _text.SetText(text);
}

std::string Text::getText() const {
  return _text.GetText();
}

void Text::draw(sf::RenderWindow &window) const {
  window.Draw(_text);
}



ValueText::Listener::Listener() {
}

ValueText::Listener::~Listener() {
}




ValueText::ValueText(Frame frame, int value, ValueText::Listener *pListener) :
    Text(frame, makeTextFromValue(value)),
    _value(value),
    _pListener(pListener) {
}

ValueText::~ValueText() {
}

std::string ValueText::makeTextFromValue(int value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

void ValueText::setValue(int value) {
    _value = value;
    _text.SetText(makeTextFromValue(_value));
    if (_pListener)
        _pListener->notifyChangedValue(*this);
    maj();
}

int ValueText::getValue() const {
    return _value;
}
