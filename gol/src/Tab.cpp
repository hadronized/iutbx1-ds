#include <cassert>
#include "Tab.hpp"

TabList::Listener::Listener() {
}

TabList::Listener::~Listener() {
}

TabList::TabList(Frame frame, sf::Sprite sprite, Listener *pListener) :
    WidgetComposite(frame, sprite),
    _pListener(pListener) {
    onChangedFrame();
    maj();
}

TabList::~TabList() {
}

void TabList::onChangedFrame() {
    float w = _frame.getWidth() / _widgets.size();
    Frame f(0, _frame.getPY(), w, _frame.getHeight());

    WidgetList::iterator end = _widgets.end();
    int i = 0;
    for (WidgetList::iterator it = _widgets.begin(); it != end; ++it, ++i) {
        f.setPX(_frame.getPX() + w*i);
        (*it)->setFrame(f);
    }
}

void TabList::setListener(TabList::Listener *pListener) {
    assert(pListener);
    _pListener = pListener;
}

WidgetBase & TabList::add(WidgetBase *widget) {
    WidgetComposite::add(widget);
    maj();
    return *widget;
}

int TabList::getActive() const {
    return _active;
}

bool TabList::relayEvents(sf::Event const &event, sf::Input const &input) {
    if (WidgetBase::relayEvents(event, input)) {
        _active = -1; // par defaut, rien n'est actif
        if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) { // clic gauche
            for (int i = 0; i < _widgets.size(); ++i) {
                if (_widgets[i]->relayEvents(event, input)) { // evenement capture par l'un des widgets de l'arborescence
                    _active = i;
		    if (_pListener) // si un listener est attache, on notify le changement de tab
			_pListener->notifyTabChanged(*this);
		} else {
                    _widgets[i]->reset(); // reinitialise le bouton en unchecked
		}
            }
        }

        return true;
    }

    return false;
}
