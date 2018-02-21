#pragma once
#include "GameModel.h"

enum class GameViewEvent{StartNewGame,DoFirstTry,DoSecondTry,EliminateDoor};

class GameController
{
private:
	GameModel& gameModel_;
	void doFirstTry_(int index);
	void doSecondTry_(int index);
public:
	GameController(GameModel&);
	~GameController();
	void pickDoorCommand(int);
	void eliminateDoorCommand();
	void startNewGameCommand();
	void quitGameCommand();

	bool isWin();
};

