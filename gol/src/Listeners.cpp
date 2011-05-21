#include <cassert>
#include "Listeners.hpp"
#include "Model.hpp"
#include "View.hpp"

PauseListener::PauseListener() :
    _pause(true) {
}

PauseListener::~PauseListener(){}

bool PauseListener::isPause() const {
  return _pause;
}

void PauseListener::notifyToggle(ToggleButton &sender) {
  _pause = sender.is_checked();
}


GameColListener::GameColListener(GameView *pGV, GameModel *pGM) :
    ValueText::Listener(),
    _pGV(pGV),
    _pGM(pGM) {
}

GameColListener::~GameColListener() {
}

void GameColListener::notifyChangedValue(ValueText &sender) {
    _pGM->setCol(sender.getValue());
    _pGV->maj();
}



GameRowListener::GameRowListener(GameView *pGV, GameModel *pGM) :
    ValueText::Listener(),
    _pGV(pGV),
    _pGM(pGM) {
}

GameRowListener::~GameRowListener() {
}

void GameRowListener::notifyChangedValue(ValueText &sender) {
    _pGM->setRow(sender.getValue());
    _pGV->maj();
}



SpeedListener::SpeedListener(GameView *pGV) :
    Slider::Listener(),
    _pGV(pGV) {
    assert(pGV);
}

SpeedListener::~SpeedListener() {
}

void SpeedListener::notifyChangedValue(Slider &sender) {
    float s = (sender.getMax() - sender.getValue()) / 1000.f;
    
    if (s <= 0.f)
	s = 0.002f; // limite, un peu moche ca ... magic hack :)
    _pGV->setSpeed(s);
}



MinAliveListener::MinAliveListener(GameModel *pGM) :
    Slider::Listener(),
    _pGM(pGM) {
    assert(pGM);
}

MinAliveListener::~MinAliveListener() {
}

void MinAliveListener::notifyChangedValue(Slider &sender) {
    _pGM->setMinAlive(sender.getValue());
}




MaxAliveListener::MaxAliveListener(GameModel *pGM) :
    Slider::Listener(),
    _pGM(pGM) {
    assert(pGM);
}

MaxAliveListener::~MaxAliveListener() {
}

void MaxAliveListener::notifyChangedValue(Slider &sender) {
    _pGM->setMaxAlive(sender.getValue());
}



MinDeadListener::MinDeadListener(GameModel *pGM) :
    Slider::Listener(),
    _pGM(pGM) {
    assert(pGM);
}

MinDeadListener::~MinDeadListener() {
}

void MinDeadListener::notifyChangedValue(Slider &sender) {
    _pGM->setMinDead(sender.getValue());
}



MaxDeadListener::MaxDeadListener(GameModel *pGM) :
    Slider::Listener(),
    _pGM(pGM) {
    assert(pGM);
}

MaxDeadListener::~MaxDeadListener() {
}

void MaxDeadListener::notifyChangedValue(Slider &sender) {
    _pGM->setMaxDead(sender.getValue());
}



AddVirusListener::AddVirusListener(GameView *pGV) :
    PushButton::Listener(),
    _pGV(pGV) {
}

AddVirusListener::~AddVirusListener() {
}

void AddVirusListener::notifyUp(PushButton &sender) {
    _pGV->addVirus();

}



RemoveLastVirusListener::RemoveLastVirusListener(GameView *pGV) :
    PushButton::Listener(),
    _pGV(pGV) {
}

RemoveLastVirusListener::~RemoveLastVirusListener() {
}

void RemoveLastVirusListener::notifyUp(PushButton &sender) {
    _pGV->popBackVirus();

}



RemoveAllVirusListener::RemoveAllVirusListener(GameView *pGV) :
    PushButton::Listener(),
    _pGV(pGV) {
}

RemoveAllVirusListener::~RemoveAllVirusListener() {
}

void RemoveAllVirusListener::notifyUp(PushButton &sender) {
    _pGV->removeViruses();

}



SaveListener::SaveListener(GameModel *pGM):
  PushButton::Listener(), _pGM(pGM) 
{
}

SaveListener::~SaveListener()
{
}

void SaveListener::notifyUp(PushButton &sender) {
    _pGM->save();
}



LoadListener::LoadListener(GameModel *pGM):
  PushButton::Listener(), _pGM(pGM) 
{
}

LoadListener::~LoadListener()
{
}

void LoadListener::notifyUp(PushButton &sender) {
    _pGM->load();
}



IncubListener::IncubListener(GameView *pGV) :
    Slider::Listener(),
    _pGV(pGV) {
}

IncubListener::~IncubListener() {
}

void IncubListener::notifyChangedValue(Slider &sender) {
    _pGV->setIncubTime(sender.getValue());
}



DivideVirusListener::DivideVirusListener(GameView *pGV) :
    Slider::Listener(),
    _pGV(pGV) {
}

DivideVirusListener::~DivideVirusListener() {
}

void DivideVirusListener::notifyChangedValue(Slider &sender) {
    _pGV->setDivideVirus(sender.getValue());
}
