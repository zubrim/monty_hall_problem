#pragma once
#include "GameView.h"

class GameViewConsole : public GameView
{
public:
	GameViewConsole(GameModel&,GameController&);
	~GameViewConsole();
	void showReady() override;
	void showFirstTryDone() override;
	void showSecondTryDone() override;
	void showDoorEliminated() override;
	void update() override;
	void printDoors();
};

