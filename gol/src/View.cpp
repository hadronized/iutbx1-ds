#include <cassert>
#include <SFML/System/Clock.hpp>
#include "View.hpp"
#include "Model.hpp"

#include "Intro.hpp"

using namespace std;
using namespace sf;

//=======================================
// Constructeur
//=======================================
GameView::GameView(int w, int h, GameModel *pModel) : 
    _w(w),
    _h(h),
    _frameBG(_w/4, 0, _w-_w/4, _h),
    _speed(0.20f),
    _incubTime(2),
    _divideVirus(2),
    _rowListener(this, pModel),
    _colListener(this, pModel), 
    _speedListener(this),
    _minaListener(pModel),
    _maxaListener(pModel),
    _mindListener(pModel),
    _maxdListener(pModel),
    _addvListener(this),
    _removelvListener(this),
    _removeavListener(this),
    _model(pModel),
    _saveListener(pModel),
    _loadListener(pModel),
    _incubListener(this),
    _dividevListener(this) {
    Introduction intro;

    _window = new RenderWindow(sf::VideoMode(w, h, 32), "Game of Life", sf::Style::Close);

    intro.draw(*_window, _cell_image, _cell_sprite);
    // _model->load();
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    //   CONFIGURATION WIDGETS
    // /!\ GERER LE FAIT QUE CERTAINS WIDGETS N'ONT PAS DE SPRITE, COMME LES COMPOSITES, CE N'EST PAS FRANCHEMENT GENANT MAIS CAY MAAAAAAL !!1
    initPannel();
    createCellPage();
    createVirusPage();
}

//=======================================
// Destructeur
//=======================================
GameView::~GameView() {
    if(_window != NULL)
        delete _window;
    if (_pPannel != NULL)
        delete _pPannel;
}

void GameView::initPannel() {
    // chargement images
    _button_cell_image_checked.LoadFromFile("data/button_cell_checked.png");
    _button_cell_image_unchecked.LoadFromFile("data/button_cell_unchecked.png");
    _pannel_image.LoadFromFile("data/pannel.png");

    _background_image.LoadFromFile("data/background.png");
    _background_sprite = sf::Sprite(_background_image);
    _background_sprite.Resize(_w, _h);
    _background_sprite.SetPosition(_w/4,0);

    _cell_image.LoadFromFile("data/cell.png");
    _cell_sprite = Sprite(_cell_image);
    _virus_image.LoadFromFile("data/virus.png");
    _virus_sprite = Sprite(_virus_image);
    maj();
    _save_image.LoadFromFile("data/save.png");
    _load_image.LoadFromFile("data/load.png");

    _add_virus_image.LoadFromFile("data/add.png");
    _erase_virus_image.LoadFromFile("data/erase.png");
    _eraseAll_virus_image.LoadFromFile("data/eraseAll.png");

    _minus_image.LoadFromFile("data/button_minus.png");
    _numeric_background_image.LoadFromFile("data/numeric_background.png");
    _plus_image.LoadFromFile("data/button_plus.png");
    _playImage.LoadFromFile("data/play.png");
    _pauseImage.LoadFromFile("data/pause.png");

    // onglet Cell
    ToggleButton *pCell = new ToggleButton( Frame(0, 0, 20, 0), Sprite(_button_cell_image_unchecked), Sprite(_button_cell_image_checked), 0, true, true, "Cell" );
    // onglet virus
    ToggleButton *pVirus = new ToggleButton( Frame(0, 0, 20, 0), Sprite(_button_cell_image_unchecked), Sprite(_button_cell_image_checked), 0, false, true, "Virus");


    // list d'onglets
    TabList *pTabList = new TabList( Frame(0, 0, 0, _h/16), Sprite() );
    pTabList->add(pCell);
    pTabList->add(pVirus);

    // creation du pannel
    _pPannel = new Pannel( Frame(0, 0, _w/4, _h), Sprite(_pannel_image), pTabList );
}


void GameView::createCellPage() {
    // Numeric bar ligne
    PushButton *pPushMinusRow = new PushButton( Frame(0, 0, 46, 46), Sprite(_minus_image) );
    ValueText *pValueRow = new ValueText( Frame(0, 0, 0, 0), _model->getRow(), &_rowListener );
    PushButton *pPushPlusRow = new PushButton( Frame(0, 0, 46, 46), Sprite(_plus_image) );
    NumericBar * pNBRow = new NumericBar( Frame(0, 0, _w/6, 40), Sprite(_numeric_background_image), pPushMinusRow, pValueRow, pPushPlusRow );

    // Numeric bar colonne
    PushButton *pPushMinusCol = new PushButton( Frame(0, 0, 46, 46), Sprite(_minus_image) );
    ValueText *pValueCol = new ValueText( Frame(0, 0, 0, 0), _model->getCol(), &_colListener );
    PushButton *pPushPlusCol = new PushButton( Frame(0, 0, 46, 46), Sprite(_plus_image) );
    NumericBar * pNBCol = new NumericBar( Frame(0, 0, _w/6, 40), Sprite(_numeric_background_image), pPushMinusCol, pValueCol, pPushPlusCol );

    // Bouton pause/play
    ToggleButton *pPausePlay = new ToggleButton( Frame(0.f, 0.f, 46, 46), Sprite(_pauseImage), Sprite(_playImage), &_pauseListener, true );

    //PushBoutton Load/Save
    PushButton *pSave = new PushButton( Frame(0, 0, 100, 35), Sprite(_save_image), &_saveListener );
    PushButton *pLoad = new PushButton( Frame(0, 0, 100, 35), Sprite(_load_image), &_loadListener );
 
    // Sliders
    _slider_bg_image.LoadFromFile("data/slider.png");
    _slider_cursor_image.LoadFromFile("data/slider_cursor.png");
    Slider *pSliderSpeed = new Slider( Frame(0, 0, _w/5, 18), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 1, 500, 500 - _speed * 1000, &_speedListener);
    Slider *pSliderMinAlive = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 0, 8, _model->getMinAlive(), &_minaListener );
    Slider *pSliderMaxAlive = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 0, 8, _model->getMaxAlive(), &_maxaListener );
    Slider *pSliderMinDead = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 0, 8, _model->getMinDead(), &_mindListener );
    Slider *pSliderMaxDead = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 0, 8, _model->getMaxDead(), &_maxdListener );

    // Textes
    Text *pMinDie = new Text( Frame(0, 0, _w/5, 15), "min cell (death) :");
    Text *pMaxDie = new Text( Frame(0, 0, _w/5, 15), "max cell (death) :");
    Text *pMinBear = new Text( Frame(0, 0, _w/5, 15), "min cell (alive) :");
    Text *pMaxBear = new Text( Frame(0, 0, _w/5, 15), "max cell (alive) :");
    Text *pTextSpeed = new Text( Frame(0, 0, _w/5, 15), "speed :");
    Text *pTextRow = new Text( Frame(0, 0, _w/5, 15), "row :");
    Text *pTextCol = new Text( Frame(0, 0, _w/5, 15), "col :");
    Text *pCellNBText = new Text( Frame(0, 0, _w/5, 15), "cell number :" );

    // Value text (compteur)
    _pCellNB = new ValueText( Frame(0, 0, _w/5, 12), 0 );
    _pSpeedNB = new ValueText( Frame(30, 30, 30, 30), (int)_speed);


    // Page cell
    Page *pPage = new Page( Frame(0, 0, 0, 0) );
    pPage->add(pMinBear);
    pPage->add(pSliderMinAlive);
    pPage->add(pMaxBear);
    pPage->add(pSliderMaxAlive);
    pPage->add(pMinDie);
    pPage->add(pSliderMinDead);
    pPage->add(pMaxDie);
    pPage->add(pSliderMaxDead);
    pPage->add(pTextSpeed);
    pPage->add(pSliderSpeed);
    pPage->add(pPausePlay);
    pPage->add(pTextRow);
    pPage->add(pNBRow);
    pPage->add(pTextCol);
    pPage->add(pNBCol);
    pPage->add(pSave);
    pPage->add(pLoad);
    pPage->add(pCellNBText);
    pPage->add(_pCellNB);
    _pPannel->add(pPage);
}


void GameView::createVirusPage() {
    // Slider incubation / enfants
    Slider *pSliderIncubation = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 1, 20, _incubTime, &_incubListener );
    Slider *pSliderDivideVirus = new Slider( Frame(0, 0, _w/5, 20), Sprite(_slider_bg_image), Sprite(_slider_cursor_image), 1, 8, _divideVirus, &_dividevListener ); 

    // PushButton ajouter virus
    PushButton *pAddVirus = new PushButton( Frame(0, 0, 46, 46), Sprite(_add_virus_image), &_addvListener );
    PushButton *pRemoveLastVirus = new PushButton( Frame(0, 0, 46, 46), Sprite(_erase_virus_image), &_removelvListener );
    PushButton *pRemoveAllViruses = new PushButton( Frame(0, 0, 46, 46), Sprite(_eraseAll_virus_image), &_removeavListener );

    // Textes
    Text *pIncubTimeText = new Text( Frame(0, 0, _w/5, 15), "incub time :" );
    Text *pVirusDivideText = new Text( Frame(0, 0, _w/5, 15), "divided children :" );
    Text *pVirusNBText = new Text( Frame(0, 0, _w/5, 15), "virus nb :" );
    Text *pVirusAddText = new Text( Frame(0, 0, _w/5, 15), "add virus :" );
    Text *pVirusRemoveLastText = new Text( Frame(0, 0, _w/5, 15), "remove last virus :" );
    Text *pVirusRemoveAllText = new Text( Frame(0, 0, _w/5, 15), "remove all viruses :" );
    

    // Value text (compteur)
    _pVirusNB = new ValueText( Frame(0, 0, _h/5, 12), 0 );

    // Page Virus
    Page *pPage = new Page( Frame(0, 0, 0, 0) );

    pPage->add(pIncubTimeText);
    pPage->add(pSliderIncubation);
    pPage->add(pVirusDivideText);
    pPage->add(pSliderDivideVirus);
    pPage->add(pVirusAddText);
    pPage->add(pAddVirus);
    pPage->add(pVirusRemoveLastText);
    pPage->add(pRemoveLastVirus);
    pPage->add(pVirusRemoveAllText);
    pPage->add(pRemoveAllViruses);
    pPage->add(pVirusNBText);
    pPage->add(_pVirusNB);


    _pPannel->add(pPage);
}

void GameView::maj() {
    sf::Vector2f size;
    _cell_sprite.Resize( 1.f * _frameBG.getWidth() / _model->getCol(), 1.f * _frameBG.getHeight() / _model->getRow() );
    size = _cell_sprite.GetSize();
    size.x /= 1.5f;
    size.y /= 1.5f;
    _virus_sprite.Resize(size);
}

void GameView::setSpeed(float s) {
    _speed = s;
}

//=======================================
// Traitement des evenements
// Retourne false si un evenement de fin est recu
//=======================================
bool GameView::treatEvents() {
    bool result = false;
    int i, j;
    if (_window->IsOpened()) {
	result = true;
	sf::Event event;
	while (_window->GetEvent(event)) {
            sf::Input const &input = _window->GetInput();

            switch (event.Type) {
                case sf::Event::Closed :
                    _window->Close();
                    result = false;
                    break;

                case sf::Event::KeyPressed :
                    switch (event.Key.Code) {
                        case sf::Key::Escape :
                            _window->Close();
                            result = false;
                            break;

                        case sf::Key::V :
                            addVirus();
                            break;
		    }
                    break;
            }
	        
            // gestion de la souris :
            //  · clic gauche appuye + deplacement souris : naissance cellule
            //  · clic droit appye + deplacement souris : mort cellule
            if (_frameBG.focused(input)) {
                i = input.GetMouseY() / _cell_sprite.GetSize().y;
		j = (input.GetMouseX() - _frameBG.getPX()) / _cell_sprite.GetSize().x;
                sf::Vector2f pos(_frameBG.getPX()+_cell_sprite.GetSize().x*j, _cell_sprite.GetSize().y*i);
		sf::Vector2f oth = pos + _cell_sprite.GetSize();

		_selection = sf::Shape::Rectangle(pos.x, pos.y, oth.x, oth.y, sf::Color(182, 182, 182));

                if (input.IsMouseButtonDown(sf::Mouse::Left)) {
                    _model->makeAlive(i, j);
                } else if (input.IsMouseButtonDown(sf::Mouse::Right)) {
                    _model->kill(i, j);
                }
            } else {
                _pPannel->relayEvents(event, input);
            }
	}
    }  

    return result;
}

void GameView::draw() {
    int speed = _speed;

    VirusList::iterator end = _viruses.end();

    _window->Draw(_background_sprite);
    _pPannel->draw(*_window);

    _window->Draw(_selection);
        
    for (int i = 0; i < _model->getRow(); ++i) {
        for (int j = 0; j < _model->getCol(); ++j) {
	    if (_model->isAlive(i, j)) {
		_cell_sprite.SetPosition(_cell_sprite.GetSize().x*j+_frameBG.getPX(), _cell_sprite.GetSize().y*i);
		_window->Draw(_cell_sprite);
	    }
        }
    }

    for (VirusList::iterator it = _viruses.begin(); it != end; ++it) {
        _virus_sprite.SetPosition(it->getPosition());
        _window->Draw(_virus_sprite);
    }

    _window->Display();
    usleep(500);
}

#include <iostream>
void GameView::game() {
    int neight = 0;
    int i, j;
    VirusList::iterator end = _viruses.end();

    if (!_pauseListener.isPause()) {
        for (VirusList::iterator it = _viruses.begin(); it != end; ++it) {
            i = (it->getPosition().y+_virus_sprite.GetSize().y/2) / _cell_sprite.GetSize().y;
            j = (it->getPosition().x+_virus_sprite.GetSize().x/2 - _frameBG.getPX()) / _cell_sprite.GetSize().x;
            sf::Vector2f pos = sf::Vector2f(it->getPosition().x + _virus_sprite.GetSize().x/2, it->getPosition().y + _virus_sprite.GetSize().y/2);
            
	    if (i < 0) i = 0;
	    else if (i >= _model->getRow()) i = _model->getRow()-1;
	    if (j < 0) j = 0;
	    else if (j >= _model->getCol()) j = _model->getCol()-1;
	    if (it->collideCell(_model->isAlive(i, j), pos, _cell_sprite.GetSize(), _virus_sprite.GetSize())) { // colision avec une cellule
                it->keepAlive(); // le virus ne doit pas mourrir pendant l'incubation
                
                if ( _cellClock.GetElapsedTime() >= _speed)
                    it->incub();

                if (it->getIncub() >= _incubTime) {
                    _model->kill(i, j);
                    divideVirus(pos);
                    it->setNoIncub();
                }
            } else { // pas de collision
                it->setNoIncub();

                if (_virusClock.GetElapsedTime() >= _speed/5) {
                    it->move(Frame(_frameBG.getPX(), _frameBG.getPY(), _frameBG.getWidth()-_virus_sprite.GetSize().x, _frameBG.getHeight()-_virus_sprite.GetSize().y));
		}

                if ( _cellClock.GetElapsedTime() >= _speed) {
                    it->degenerate();
                    if (it->isDegenerated()) {
                        VirusList::iterator t = it;
                        ++it;
                        
                        _viruses.erase(t);
                        _pVirusNB->setValue(_viruses.size());
                    }
                }
            }
        }
        
        if (_virusClock.GetElapsedTime() >= _speed/5)
            _virusClock.Reset();

	if( _cellClock.GetElapsedTime() >= _speed) {
	    neight = _model->next();
	    _pCellNB->setValue(neight);
	    _cellClock.Reset();
	}
    }

    draw();
}

void GameView::addVirus() {
    _viruses.push_back( Virus( Frame(_frameBG.getPX(), _frameBG.getPY(), _frameBG.getWidth()-_virus_sprite.GetSize().x, _frameBG.getHeight()-_virus_sprite.GetSize().y) ) );
    _pVirusNB->setValue(_viruses.size());
}

void GameView::popBackVirus() {
    if (!_viruses.empty()) {
	_viruses.pop_back(); // si pas de virus, ne fait rien
	_pVirusNB->setValue(_viruses.size());
    }
}

void GameView::removeViruses() {
    _viruses.clear();
    _pVirusNB->setValue(_viruses.size());
}

void GameView::setIncubTime(int time) {
    _incubTime = time;
}

void GameView::setDivideVirus(int d) {
    _divideVirus = d;
}

void GameView::divideVirus(sf::Vector2f const &pos) {
    sf::Vector2f p;
    for (int i = 0; i < _divideVirus; ++i) {
	do {
	    p = pos;
	    p.x += 1.f * (rand() % static_cast<int>(2*_cell_sprite.GetSize().x) - _cell_sprite.GetSize().x);
	    p.y += 1.f * (rand() % static_cast<int>(2*_cell_sprite.GetSize().y) - _cell_sprite.GetSize().y);
	} while (p.x >= _w || p.y >= _h);

	_viruses.push_back( Virus(p) );
    }
    _pVirusNB->setValue(_viruses.size());
}
