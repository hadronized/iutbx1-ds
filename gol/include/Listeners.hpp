#ifndef LISTENERS_HPP
#define LISTENERS_HPP

#include "Button.hpp"
#include "Slider.hpp"
#include "Text.hpp"

// forward declaration
class GameModel;
class GameView;

class PauseListener : public ToggleButton::Listener {
private :
    bool _pause;
public :
    PauseListener();
    ~PauseListener();
    bool isPause() const;  
    void notifyToggle(ToggleButton &sender );
};


class GameRowListener : public ValueText::Listener {
private :
    GameView *_pGV;
    GameModel * _pGM;

public :
    GameRowListener(GameView *pGV, GameModel *pGM);
    ~GameRowListener(void);
    
    void notifyChangedValue(ValueText &sender);
};



class GameColListener : public ValueText::Listener {
private :
    GameView *_pGV;
    GameModel * _pGM;

public :
    GameColListener(GameView *pGV, GameModel *pGM);
    ~GameColListener(void);

    void notifyChangedValue(ValueText &sender);
};



class SpeedListener : public Slider::Listener {
private :
    GameView *_pGV;

public :
    SpeedListener(GameView *pGV);
    ~SpeedListener(void);

    void notifyChangedValue(Slider &sender);
};



class MinAliveListener : public Slider::Listener {
private :
    GameModel *_pGM;

public :
    MinAliveListener(GameModel *pGM);
    ~MinAliveListener(void);

    void notifyChangedValue(Slider &sender);
};



class MaxAliveListener : public Slider::Listener {
private :
    GameModel *_pGM;

public :
    MaxAliveListener(GameModel *pGM);
    ~MaxAliveListener(void);

    void notifyChangedValue(Slider &sender);
};



class MinDeadListener : public Slider::Listener {
private :
    GameModel *_pGM;

public :
    MinDeadListener(GameModel *pGM);
    ~MinDeadListener(void);

    void notifyChangedValue(Slider &sender);
};



class MaxDeadListener : public Slider::Listener {
private :
    GameModel *_pGM;

public :
    MaxDeadListener(GameModel *pGM);
    ~MaxDeadListener(void);

    void notifyChangedValue(Slider &sender);
};




class AddVirusListener : public PushButton::Listener {
private :
    GameView *_pGV;

public :
    AddVirusListener(GameView *pGV);
    ~AddVirusListener(void);

    void notifyUp(PushButton &sender);
};




class RemoveLastVirusListener : public PushButton::Listener {
private :
    GameView *_pGV;

public :
    RemoveLastVirusListener(GameView *pGV);
    ~RemoveLastVirusListener(void);

    void notifyUp(PushButton &sender);
};



class RemoveAllVirusListener : public PushButton::Listener {
private :
    GameView *_pGV;

public :
    RemoveAllVirusListener(GameView *pGV);
    ~RemoveAllVirusListener(void);

    void notifyUp(PushButton &sender);
};



class SaveListener : public PushButton::Listener {
private :
    GameModel *_pGM;

public :
    SaveListener(GameModel *pGM);
    ~SaveListener(void);

    void notifyUp(PushButton &sender);
};



class LoadListener : public PushButton::Listener {
private :
    GameModel *_pGM;

public :
    LoadListener(GameModel *pGM);
    ~LoadListener(void);

    void notifyUp(PushButton &sender);
};



class IncubListener : public Slider::Listener {
private :
    GameView *_pGV;

public :
    IncubListener(GameView *pGV);
    ~IncubListener(void);

    void notifyChangedValue(Slider &sender);
};



class DivideVirusListener : public Slider::Listener {
private :
    GameView *_pGV;

public :
    DivideVirusListener(GameView *pGV);
    ~DivideVirusListener(void);

    void notifyChangedValue(Slider &sender);
};

#endif // guard
