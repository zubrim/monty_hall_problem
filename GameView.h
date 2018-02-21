#pragma once
#include "Observer.h"
#include "GameModel.h"
#include "GameController.h"

class GameView : public Observer
{
protected:
	GameModel& gameModel_;
	GameController& gameController_;
public:
	GameView(GameModel&, GameController&);
	~GameView();
	virtual void showReady();
	virtual void showFirstTryDone();
	virtual void showSecondTryDone();
	virtual void showDoorEliminated();

	virtual void update();
};