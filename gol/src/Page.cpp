#include "Page.hpp"

int const Page::PADDING = 5;

Page::Page(Frame frame) :
    WidgetComposite(frame, sf::Sprite()) {
    onChangedFrame();
    maj();
}

Page::~Page() {
}

void Page::onChangedFrame() {
    float py = 0;
    for (int i = 0; i < _widgets.size(); ++i) {
        Frame f = _widgets[i]->getFrame();
        f.setPX( _frame.getPX() + (_frame.getWidth()-f.getWidth())/2 ); // widgets places en milieu de page
        f.setPY( _frame.getPY() + py ); // widgets ajoutes de haut en bas
        py += f.getHeight() + PADDING;
        //f.setWidth( _frame.getWidth() ); // commenter pour eviter d'avoir des objets etires
        _widgets[i]->setFrame(f);
    }
}

WidgetBase & Page::add(WidgetBase *widget) {
    // on doit forcer la largeur du widget et le positionner sous les autres widgets
    Frame f(_frame.getPX()+(_frame.getWidth()-widget->getFrame().getWidth())/2, 0.f, widget->getFrame().getWidth(), widget->getFrame().getHeight());

    if (!_widgets.empty()) {
        Frame lastFrame = _widgets.back()->getFrame();
        f.setPY(lastFrame.getPY() + lastFrame.getHeight());
    }
    
    widget->setFrame(f);
    WidgetComposite::add(widget);
    return *widget;
}
