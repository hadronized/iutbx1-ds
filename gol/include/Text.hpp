#ifndef VALUE_TEXT_HPP
#define VALUE_TEXT_HPP

#include  "Widget.hpp"

class Text : public WidgetBase {
protected :
    sf::String _text;

public :
    Text(Frame frame, std::string const &text);
    ~Text(void);

    void maj(void); // necessaire car on n'utilise pas de Sprite !

    void setText(std::string const &text);
    std::string getText(void) const;

    void draw(sf::RenderWindow &window) const;
};



class ValueText : public Text {
public :
    class Listener {
    public :
        Listener(void);
        ~Listener(void);

        virtual void notifyChangedValue(ValueText &sender) = 0;
    };

private :
    int _value;
    Listener *_pListener;

    std::string makeTextFromValue(int value);

public :
    ValueText(Frame frame, int value, Listener *pListener = 0);
    ~ValueText(void);

    void setValue(int value);
    int getValue(void) const;
};

#endif // guard
