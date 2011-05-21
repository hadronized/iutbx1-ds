#ifndef PANNEL_HPP
#define PANNEL_HPP

#include "Widget.hpp"
#include "Tab.hpp"
#include "Page.hpp"

class Pannel : public WidgetComposite {
private :
    /**
     * Listener d'onglets. Cette classe permet de surveiller la liste d'onglets
     * afin de savoir quel onglet afficher.
     */
    class TBListener : public TabList::Listener {
	int _active;

    public :
	TBListener(void);
	~TBListener(void);

	void notifyTabChanged(TabList const &sender);
	int getActive(void) const;
    };

    TabList *_pTbl;
    TBListener _tblistener;
    static int const UP_MARGIN;

    void onChangedFrame(void);

public :
    Pannel(Frame frame, sf::Sprite sprite, TabList *pTbl);
    ~Pannel(void);

    WidgetBase & add(WidgetBase *widget); // interdit
    Page & add(Page *pPage);

    void draw(sf::RenderWindow &window) const;
    bool relayEvents(sf::Event const &event, sf::Input const &input);
};

#endif // guard
