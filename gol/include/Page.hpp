#ifndef PAGE_HPP
#define PAGE_HPP

#include "Widget.hpp"

class Page : public WidgetComposite {
private :
    void onChangedFrame(void);

    static int const PADDING;

public :
    Page(Frame frame);
    ~Page(void);

    WidgetBase & add(WidgetBase *widget);
};

#endif
