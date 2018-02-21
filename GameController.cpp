#include "GameController.h"
#include <iostream>

GameController::GameController(GameModel& gameModel) :
	gameModel_(gameModel)
{}

GameController::~GameController(){}

void GameController::pickDoorCommand(int index) {
	if (gameModel_.getDoorState(index) == DoorState::ELIMINATED) return;
	switch (gameModel_.getState()) {
	case GameEngineState::READY: doFirstTry_(index); break;
	case GameEngineState::DOOR_ELIMINATED: doSecondTry_(index); break;
	default: break;
	}
};
void GameController::eliminateDoorCommand() {
	gameModel_.changeStateTo(GameEngineState::DOOR_ELIMINATED);
};
void GameController::startNewGameCommand() {
	gameModel_.changeStateTo(GameEngineState::READY);
};

void GameController::quitGameCommand() {
	gameModel_.changeStateTo(GameEngineState::QUIT);;
};

void GameController::doFirstTry_(int index) {
	gameModel_.changeStateTo(GameEngineState::FIRST_TRY_DONE, index);
}
void GameController::doSecondTry_(int index) {
	gameModel_.changeStateTo(GameEngineState::SECOND_TRY_DONE, index);
}

bool GameController::isWin() { return gameModel_.isCarWon(); }