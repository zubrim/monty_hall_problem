#pragma once
#include "Observable.h"
#include "GameEngine.h"
#include <string>

class GameModel : public Observable
{
private:
	GameEngine gameEngine_;
public:
	GameModel();
	~GameModel();
	void changeStateTo(GameEngineState state);
	void changeStateTo(GameEngineState state,int index);

	// useful GameEngine getters to use in GameModel
	GameEngineState getState();
	int getNumberOfDoors();

	DoorState getDoorState(int index);
	std::string getDoorStateText(int index);
	std::string getDoorContentText(int index);
	bool isCarWon();
};

