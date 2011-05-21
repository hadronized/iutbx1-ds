#ifndef TAB_HPP
#define TAB_HPP

#include "Widget.hpp"
#include "Button.hpp"

class TabList : public WidgetComposite {
public :
    class Listener {
    public :
	Listener(void);
	~Listener(void);

	virtual void notifyTabChanged(TabList const &sender) = 0;
    };

protected :
    int _active; // indice de l'onglet actif
    Listener *_pListener;
    
    void onChangedFrame(void);

public :
    TabList(Frame frame, sf::Sprite sprite, Listener *pListener = 0);
    ~TabList(void);

    void setListener(Listener *pListener); // assigne un nouveau listener pour surveiller le TabList

    /*
     * Ajoute un widget representant un onglet a la liste d'onglet. Cette methode est remplacee car elle fonctionne en tiling :
     * quand la liste d'onglets ne possede qu'un onglet, l'onglet prend toute la place de la liste. Si on en ajoute un, chaque onglet prend
     * la moitie de la place disponible, etc etc ...
     */
    WidgetBase & add(WidgetBase *widget);
    /*
     * Retourne l'indice de l'onglet actif. Indispensable pour savoir quelle page afficher par la suite.
     */
    int getActive(void) const;
    bool relayEvents(sf::Event const &event, sf::Input const &input);
};

#endif
