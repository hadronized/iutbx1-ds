#include <cassert>
#include "Pannel.hpp"

int const Pannel::UP_MARGIN = 20; // 20 pixels de marge

Pannel::TBListener::TBListener() :
    TabList::Listener(),
    _active(0) { // on part du principe que le premier onglet est actif
}

Pannel::TBListener::~TBListener() {
}

void Pannel::TBListener::notifyTabChanged(TabList const &sender) {
    _active = sender.getActive();
    assert(_active >= 0);
}

int Pannel::TBListener::getActive() const {
    return _active;
}

Pannel::Pannel(Frame frame, sf::Sprite sprite, TabList *pTbl) :
    WidgetComposite(frame, sprite),
    _pTbl(pTbl) {
    onChangedFrame();
    maj();
    assert(_pTbl);
    _pTbl->setFrame( Frame(_frame.getPX(), _frame.getPY(), _frame.getWidth(), _pTbl->getFrame().getHeight()) );

    // ajout du listener a la liste d'onglets
    _pTbl->setListener(&_tblistener);
}

Pannel::~Pannel() {
}

void Pannel::onChangedFrame() {
    WidgetList::iterator end = _widgets.end();

    // changement de frame de la liste d'onglets
    Frame f = _frame;
    float h = _pTbl->getFrame().getHeight();
    _pTbl->setFrame( Frame(f.getPX(), f.getPY(), f.getWidth(), h) );

    // changement de frame de toutes les pages
    f.setPY( f.getPY() + h + UP_MARGIN );
    f.setHeight( f.getHeight() - (h + UP_MARGIN) );
    for (WidgetList::iterator it = _widgets.begin(); it != end; ++it)
        (*it)->setFrame(f);
}

WidgetBase & Pannel::add(WidgetBase *widget) {
    assert(false);
}

Page & Pannel::add(Page *pPage) {
    assert(pPage);

    Frame f = _frame;
    float tmp = _pTbl->getFrame().getHeight() + UP_MARGIN;

    f.setHeight(f.getHeight() - tmp);
    f.setPY(f.getPY() + tmp);
    pPage->setFrame(f);
    _widgets.push_back(pPage);
}

void Pannel::draw(sf::RenderWindow &window) const {
    int i = _tblistener.getActive();
    WidgetBase::draw(window); // dessine le pannel lui meme (en l'occurence son background)

    _pTbl->draw(window); // dessine la liste d'onglets
    if (i >= 0 && i < _widgets.size())
        _widgets[_tblistener.getActive()]->draw(window); // dessine la page courante
}

bool Pannel::relayEvents(sf::Event const &event, sf::Input const &input) {
    if (WidgetBase::relayEvents(event, input)) {
        int i = _tblistener.getActive();
        if (_pTbl->relayEvents(event, input)) {
        } else if (i >= 0 && i < _widgets.size()) {
            if (_widgets[i]->relayEvents(event, input));
        }

        return true;
    }

    return false;
}
