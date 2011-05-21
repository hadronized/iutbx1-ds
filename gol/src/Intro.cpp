#include <cmath>
#include "Intro.hpp"
#include <SFML/Audio.hpp>
#include <time.h>


Introduction::Introduction() {
}

Introduction::~Introduction() {
}

void Introduction::draw(sf::RenderWindow &window, sf::Image image, sf::Sprite sprite) {
    sf::Font arialRounded; 
    if(!arialRounded.LoadFromFile("data/rounded.ttf"))
    {
    }
    sf::String msgGo("Please enter the return key ...");
    msgGo.SetFont(arialRounded);
    float px, py;
    bool show = true;
    sf::Event event;
    sf::Clock clk;
    sf::Clock clkTxt;
    sf::Clock miscClk;
    float w;
    float l;
    float pcy = 0;
    float pcx = 0;
    px = 0;
    msgGo.SetSize(20);
    py = 0;
    msgGo.SetPosition(px, py);
    w = msgGo.GetRect().GetWidth();
 
    sf::SoundBuffer CellBuffer;
    if (!CellBuffer.LoadFromFile("data/son2.wav"))
    {
     
    }
    sf::Sound CellSound(CellBuffer);
 
 
    _back_image.LoadFromFile("data/introduction.png");
    _back_sprite.SetImage(_back_image);
    _back_sprite.Resize( window.GetWidth(), window.GetHeight() );
 
    if (!image.LoadFromFile("data/cell.png")) {
        sprite = sf::Sprite();
    } else {
        sprite = sf::Sprite(image);
        sprite.Resize( 35, 35);
    }
    clkTxt.Reset(); 
    clk.Reset();
    miscClk.Reset();
    float tabY[200];
    int tabX[200];
    tabX[0]=0;
    for (int i = 0; i < 200; i++)
        tabY[i] = rand() % 400 +1;
 
    for (int j = 1; j<200; j++){
        tabX[j]=tabX[j-1]+20;
    }
 

    while (show) {
        window.Draw(_back_sprite);
        for (int k = 0; k < 100; k++){
            if (sprite.GetPosition().y < 300)
                window.Draw(sprite);
            if (sprite.GetPosition().y == 300)
                CellSound.Play();
            sprite.SetY(pcy-tabY[k]);
            sprite.SetX(pcx+tabX[k]);
            if (sprite.GetPosition().y == 400)
                CellSound.Play();
        }
        if (clk.GetElapsedTime() > 0.01) {
            pcy += 3.f;
            clk.Reset();
        }
        if (clkTxt.GetElapsedTime() > 4.f) 
        {
            CellSound.Stop();
            px = 150.f;
            py = 100.f;
            window.Draw(msgGo);
            l = 35*std::cos(4 * miscClk.GetElapsedTime());
            msgGo.SetSize(l > 60 ? l : 60);
            msgGo.SetPosition(px, py + l);
            msgGo.SetColor( sf::Color( rand() % 50 + 1, rand() % 50 + 1,  rand() % 50 + 1) );
       
        }    
        window.GetEvent(event);
        window.Display();
        
        if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return) show = false;
    }
    CellSound.Stop();
}

