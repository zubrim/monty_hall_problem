#pragma once
#include "GameController.h"
#include "GameViewConsole.h"
#include "GameViewGUI.h"
#include <iostream>

int main() {
	GameModel gameModel;
	GameController gameController(gameModel);
	//GameViewConsole gameViewConsole(gameModel, gameController);
	GameViewGUI gameViewGUI(gameModel,gameController);
	gameController.startNewGameCommand();
	return 0;
}