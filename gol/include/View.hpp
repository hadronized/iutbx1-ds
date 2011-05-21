#ifndef VIEW_HPP
#define VIEW_HPP

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Button.hpp"
#include "Frame.hpp"
#include "Listeners.hpp"
#include "NumericBar.hpp"
#include "Page.hpp"
#include "Pannel.hpp"
#include "Slider.hpp"
#include "Virus.hpp"

typedef std::list<Virus> VirusList;

class GameView {
private :
    int _w, _h;
    float _speed;
    int _incubTime;
    int _divideVirus;

    sf::Clock _cellClock;
    sf::Clock _virusClock;
    sf::RenderWindow * _window;

    // simulation
    sf::Image _background_image;
    sf::Image _cell_image;
    sf::Image _virus_image;
    sf::Image _load_image;
    sf::Image _save_image;
    // cell
    sf::Image _button_cell_image_checked;
    sf::Image _button_cell_image_unchecked;
    // virus
    sf::Image _button_virus_image;
    sf::Image _add_virus_image;
    sf::Image _erase_virus_image;
    sf::Image _eraseAll_virus_image;
    // numeric bar
    sf::Image _minus_image;
    sf::Image _numeric_background_image;
    sf::Image _plus_image;
    // image bouton pause
    sf::Image _playImage;
    sf::Image _pauseImage;
    // image slider
    sf::Image _slider_bg_image;
    sf::Image _slider_cursor_image;
    // pannel
    sf::Image _pannel_image;

    sf::Sprite _background_sprite;
    sf::Sprite _cell_sprite;
    sf::Sprite _virus_sprite;
    sf::Sprite _cellPage_sprite;

    sf::Shape _selection;

    Frame _frameBG;
    Pannel *_pPannel;
    ValueText *_pCellNB;
    ValueText *_pVirusNB;
    ValueText *_pSpeedNB;

    // Listeners
    PauseListener _pauseListener;
    GameRowListener _rowListener;
    GameColListener _colListener;
    SpeedListener _speedListener;
    MinAliveListener _minaListener;
    MaxAliveListener _maxaListener;
    MinDeadListener _mindListener;
    MaxDeadListener _maxdListener;
    AddVirusListener _addvListener;
    RemoveLastVirusListener _removelvListener;
    RemoveAllVirusListener _removeavListener;
    SaveListener _saveListener;
    LoadListener _loadListener;
    IncubListener _incubListener;
    DivideVirusListener _dividevListener;

    GameModel *_model;
    VirusList _viruses; // liste de virus

    // methodes privees
    void initPannel(void);
    void createCellPage(void);
    void createVirusPage(void);
    void createStatsPage(void);

public :
    GameView(int w, int h, GameModel *pModel);
    ~GameView();

    void maj(void);
    void setSpeed(float s);
    bool treatEvents();
    void draw();
    void game();

    void addVirus(void);
    void popBackVirus(void);
    void removeViruses(void);
    void setIncubTime(int time);
    void setDivideVirus(int d);
    void divideVirus(sf::Vector2f const &pos);
};

#endif // guard
