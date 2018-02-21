#include "GameModel.h"



GameModel::GameModel() : gameEngine_(GameEngine()){
}


GameModel::~GameModel(){}

void GameModel::changeStateTo(GameEngineState state) {
	switch (state) {
	case GameEngineState::READY: gameEngine_.reset(); break;
	case GameEngineState::DOOR_ELIMINATED: gameEngine_.eliminateDoor(); break;
	case GameEngineState::QUIT: gameEngine_.quit(); break;
	}
	gameEngine_.print();
	notifyUpdate();
}

void GameModel::changeStateTo(GameEngineState state, int index) {
	switch (state) {
		case GameEngineState::FIRST_TRY_DONE: gameEngine_.doFirstTry(index); break;
		case GameEngineState::SECOND_TRY_DONE: gameEngine_.doSecondTry(index); break;
	}
	gameEngine_.print();
	notifyUpdate();
}

GameEngineState GameModel::getState() {
	return gameEngine_.getState();
}

int GameModel::getNumberOfDoors() {
	return gameEngine_.getNumberOfDoors();
}

std::string GameModel::getDoorContentText(int index) {
	switch (gameEngine_.getDoorContentByIndex(index)) {
	case Prize::CAR  : return "CAR";
	case Prize::GOAT : return "GOAT";
	default: return "ERROR";
	}
};
std::string GameModel::getDoorStateText(int index) {
	switch (gameEngine_.getDoorStateByIndex(index)) {
	case DoorState::INITIAL: return "CLOSED";
	case DoorState::PICKED: return "PICKED";
	case DoorState::ELIMINATED: return "ELIMINATED";
	default: return "ERROR";
	}
};

DoorState GameModel::getDoorState(int index) { return gameEngine_.getDoorStateByIndex(index); };

bool GameModel::isCarWon() {
	return gameEngine_.isCarWon();
}
