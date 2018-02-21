#include "GameView.h"



GameView::GameView(GameModel& gameModel, GameController& gameController) 
	: gameModel_(gameModel), gameController_(gameController){
	gameModel_.addObserver(this);
}

GameView::~GameView() {}

void GameView::showReady() {};
void GameView::showFirstTryDone() {};
void GameView::showSecondTryDone() {};
void GameView::showDoorEliminated() {};

void GameView::update() {};
