#ifndef NUMERIC_BAR_HPP
#define NUMERIC_BAR_HPP

#include "Button.hpp"
#include "Text.hpp"
#include "Widget.hpp"

class NumericBar : public WidgetComposite {
public :
    class MinusListener : public PushButton::Listener {
    private :
        ValueText *_pValue;

    public :
        MinusListener(ValueText *pValue);
        ~MinusListener(void);

        void notifyUp(PushButton &sender);
    };

    class PlusListener : public PushButton::Listener {
    private :
        ValueText *_pValue;

    public :
        PlusListener(ValueText *pValue);
        ~PlusListener(void);

        void notifyUp(PushButton &sender);
    };

private :
    PushButton *_pLeft;
    ValueText *_pValue;
    PushButton *_pRight;

    // listeners
    MinusListener _mlistener;
    PlusListener _plistener;

    void onChangedFrame(void);

public :
    NumericBar(Frame frame, sf::Sprite sprite, PushButton *pLeft, ValueText *pValue, PushButton *pRight);
    ~NumericBar(void);

    void maj(void);

    bool relayEvents(sf::Event const &event, sf::Input const &input);
    void draw(sf::RenderWindow &window) const;
};

#endif // guard
