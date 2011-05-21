#include <cassert>
#include "NumericBar.hpp"

NumericBar::MinusListener::MinusListener(ValueText *pValue) :
    PushButton::Listener(),
    _pValue(pValue) {
    assert(pValue);
}

NumericBar::MinusListener::~MinusListener() {
}

void NumericBar::MinusListener::notifyUp(PushButton &sender) {
    if (_pValue->getValue() > 1)
        _pValue->setValue(_pValue->getValue()-1);
}



NumericBar::PlusListener::PlusListener(ValueText *pValue) :
    PushButton::Listener(),
    _pValue(pValue) {
    assert(pValue);
}

NumericBar::PlusListener::~PlusListener() {
}

void NumericBar::PlusListener::notifyUp(PushButton &sender) {
    _pValue->setValue(_pValue->getValue()+1);
}




NumericBar::NumericBar(Frame frame, sf::Sprite sprite, PushButton *pLeft, ValueText *pValue, PushButton *pRight) :
    WidgetComposite(frame, sprite),
    _pLeft(pLeft),
    _pValue(pValue),
    _pRight(pRight),
    _mlistener(_pValue),
    _plistener(_pValue) {
    assert(pLeft);
    assert(pValue);
    assert(pRight);
    maj();
    onChangedFrame();

    _pLeft->setListener(&_mlistener);
    _pRight->setListener(&_plistener);
}

NumericBar::~NumericBar() {
    if (_pLeft)
        delete _pLeft;
    if (_pRight)
        delete _pRight;
    if (_pValue)
        delete _pValue;
}

void NumericBar::maj() {
    Frame f = _frame;
    f.setPX( f.getPX() + f.getWidth()/4 );
    f.setWidth( f.getWidth() / 2 );

    _sprite.Resize( f.getWidth(), f.getHeight() );
    _sprite.SetPosition( f.getPX(), f.getPY() );
}

void NumericBar::onChangedFrame() {
    Frame f = Frame(_frame.getPX(), _frame.getPY(), _frame.getWidth()/4, _frame.getHeight());

    _pLeft->setFrame(f);
    f.setPX(f.getPX() + f.getWidth() + _frame.getWidth()/2);
    _pRight->setFrame(f);
    f.setWidth(_frame.getWidth()/2);
    f.setPX(f.getPX() - _frame.getWidth()/2);
    f.setPY(f.getPY() - f.getHeight()/10); // hack pour avoir une jolie police bien placee
    _pValue->setFrame(f);
}

bool NumericBar::relayEvents(sf::Event const &event, sf::Input const &input) {
    return _pLeft->relayEvents(event, input) || _pValue->relayEvents(event, input) || _pRight->relayEvents(event, input);
}

void NumericBar::draw(sf::RenderWindow &window) const {
    WidgetBase::draw(window);
    _pLeft->draw(window);
    _pValue->draw(window);
    _pRight->draw(window);
}


