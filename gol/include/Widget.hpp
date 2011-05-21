#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Frame.hpp"

class WidgetBase {
protected :
    Frame _frame;
    sf::Sprite _sprite;

public :
    WidgetBase(Frame frame, sf::Sprite sprite);
    virtual ~WidgetBase(void);

    virtual void maj(void); // met a jour le(s) sf::Sprite en fonction du frame
    virtual void reset(void); // permet de remettre a son etat d'origine un widget (pas tout le temps utile)
    /*
     * Retourne true si l'evenement a ete capture, false sinon. WidgetBase fournit une implementation par
     * defaut.
     */
    virtual bool relayEvents(sf::Event const &event, sf::Input const &input);
    virtual void draw(sf::RenderWindow &window) const; // le comportement par defaut est de dessiner le Widget normalement
    Frame getFrame(void) const;
    virtual void setFrame(Frame const &frame);
};



// design pattern : composite
class WidgetComposite : public WidgetBase {
protected :
    typedef std::vector<WidgetBase*> WidgetList;
    WidgetList _widgets;

    virtual void onChangedFrame(void) = 0; // methode appelee par un objet composite pour mettre a jour le frames de ses composants

public :
    WidgetComposite(Frame frame, sf::Sprite sprite);
    virtual ~WidgetComposite(void);

    virtual bool relayEvents(sf::Event const &event, sf::Input const &input); // le composite fournit une implementation, mais elle peut etre remplacee
    /*
     * Le comportement est desormais de dessiner toute l'arborescence sans dessiner le composite.
     * On ne dessine pas _par defaut_ le composite car souvent un composite est uniquement symbolique
     * (un regroupement de widgets par exemple). Cependant rien n'empeche de remplacer la methode pour
     * dessiner aussi le composite.
     */
    virtual void draw(sf::RenderWindow &window) const;
    virtual WidgetBase & add(WidgetBase *widget);
    void clear(void);
    void setFrame(Frame const &frame);
};    

#endif
