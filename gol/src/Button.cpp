#include "Button.hpp"
#include "Text.hpp"

ButtonBase::ButtonBase(Frame frame, sf::Sprite sprite, std::string const &text) :
  WidgetBase(frame, sprite),
  _text(frame, text){
  maj();

}

ButtonBase::~ButtonBase() {
}

void ButtonBase::maj() {
    WidgetBase::maj();
    _text.setFrame(_frame);
    _text.maj();
}

void ButtonBase::draw(sf::RenderWindow &window) const {
    WidgetBase::draw(window);
    _text.draw(window);
}



PushButton::Listener::Listener() {
}

PushButton::Listener::~Listener() {
}



PushButton::PushButton(Frame frame, sf::Sprite sprite, PushButton::Listener *pListener) :
    ButtonBase(frame, sprite),
    _pListener(pListener) {
    maj();
}

PushButton::~PushButton() {
}

void PushButton::reset() {
    _sprite.SetColor( sf::Color(255, 255, 255) );
}

bool PushButton::relayEvents(sf::Event const &event, sf::Input const &input) {
    reset();
    if (ButtonBase::relayEvents(event, input)) {
        if (input.IsMouseButtonDown(sf::Mouse::Left)) {
            _sprite.SetColor( sf::Color(127, 127, 127) );
        } else if (_pListener) {
            if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
                _pListener->notifyUp(*this);
        }
        return true;
    }

    return false;
}

void PushButton::setListener(PushButton::Listener *pListener) {
    _pListener = pListener;
}
    


ToggleButton::Listener::Listener() {
}

ToggleButton::Listener::~Listener() {
}



ToggleButton::ToggleButton(Frame frame, sf::Sprite sprite, sf::Sprite sprite2,
			   ToggleButton::Listener *pListener, bool checked,
			   bool forced, std::string const &text) :
  ButtonBase(frame, sprite, text),
  _sprite2(sprite2),
  _checked(checked),
  _forced(forced),
  _pListener(pListener) {
  maj();
  }

ToggleButton::~ToggleButton() {
}

void ToggleButton::changeAppearance() {
    if (_checked) // si le bouton est appuye
        _sprite.SetColor( sf::Color(255, 255, 255) );
    else
        _sprite.SetColor( sf::Color(127, 127, 127) );
}

void ToggleButton::maj() {
  ButtonBase::maj();
  _sprite2.SetPosition(_sprite.GetPosition());
  _sprite2.Resize(_sprite.GetSize());
}

void ToggleButton::reset() {
    _checked = false;
    _sprite.SetColor( sf::Color(127, 127, 127) );
}

void ToggleButton::draw(sf::RenderWindow &window) const {
    if (_checked)
	window.Draw(_sprite2);
    else
        window.Draw(_sprite);
    _text.draw(window);
}

bool ToggleButton::relayEvents(sf::Event const &event, sf::Input const &input) {
    if (WidgetBase::relayEvents(event, input)) { // evenement capture, on toggle
        if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) { // clic du bouton
            _checked = _forced ? true : !_checked; // force le bouton a checked si necessaire
            if (_pListener) // si un listener est attache au bouton, on lui notife le toggle
                _pListener->notifyToggle(*this);
        }
        return true;
    }

    return false; // evenement non capture
}

bool ToggleButton::is_checked() const {
    return _checked;
}

bool ToggleButton::is_forced() const {
    return _forced;
}
