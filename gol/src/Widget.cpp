#include <algorithm> // std::find
#include "Widget.hpp"
#include "Frame.hpp"

using namespace sf;

WidgetBase::WidgetBase(Frame frame, sf::Sprite sprite) :
    _frame(frame),
    _sprite(sprite) {
}

WidgetBase::~WidgetBase() {
}

void WidgetBase::maj() {
    _sprite.Resize(_frame.getWidth(), _frame.getHeight());
    _sprite.SetPosition(_frame.getPX(), _frame.getPY());
}

void WidgetBase::reset() {
}

void WidgetBase::draw(sf::RenderWindow &window) const {
    window.Draw(_sprite);
}

bool WidgetBase::relayEvents(sf::Event const &event, sf::Input const &input) {
    return _frame.focused(input);
}

Frame WidgetBase::getFrame() const {
    return _frame;
}

void WidgetBase::setFrame(Frame const &frame) {
    _frame = frame;
    maj();
}



WidgetComposite::WidgetComposite(Frame frame, sf::Sprite sprite) :
    WidgetBase(frame, sprite) {
}

WidgetComposite::~WidgetComposite() {
    clear();
}

bool WidgetComposite::relayEvents(sf::Event const &event, sf::Input const &input) {
    if (WidgetBase::relayEvents(event, input)) {
        WidgetList::iterator end = _widgets.end();

        for (WidgetList::iterator it = _widgets.begin(); it != end; ++it) {
            if ((*it)->relayEvents(event, input)) // evenement capture par l'un des widgets de l'arborescence
                return true;
        }
    }

    // on est arrive a la fin et l'evenement n'a pas ete traite
    return false;
}

void WidgetComposite::draw(sf::RenderWindow &window) const {
    WidgetList::const_iterator end = _widgets.end();

    for (WidgetList::const_iterator it = _widgets.begin(); it != end; ++it)
        (*it)->draw(window);
}

WidgetBase & WidgetComposite::add(WidgetBase *widget) {
    if (std::find(_widgets.begin(), _widgets.end(), widget) != _widgets.end()) // le widget existe deja dans le composite
        return *widget;
    
    // le widget n'existe pas encore, on peut le push back
    _widgets.push_back(widget);
    return *widget;
}

void WidgetComposite::clear() {
    WidgetList::iterator end = _widgets.end();
    
    for (WidgetList::iterator it = _widgets.begin(); it != end; ++it)
        delete *it;
    _widgets.clear();
}

void WidgetComposite::setFrame(Frame const &frame) {
    WidgetBase::setFrame(frame);
    onChangedFrame();
}
