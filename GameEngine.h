#pragma once
#include "Door.h"
#include <vector>
#include <random>


enum class GameEngineState { INIT, READY, FIRST_TRY_DONE, DOOR_ELIMINATED, SECOND_TRY_DONE, QUIT };

class GameEngine
{
private:
	GameEngineState state_;
	std::vector<Door> doors_;
	const int numDoors_{ 3 };
	Door *initiallyPickedDoor_, *finallyPickedDoor_, *eliminatedDoor_;
	unsigned seed_;
	std::default_random_engine rand_gen_;
	std::uniform_real_distribution<double> real_rand_gen_{ std::uniform_real_distribution<double>(0.0, 1.0) };
	Door* getDoorByIndex_(int);
public:
	GameEngine();
	~GameEngine();
	void reset();
	void quit();
	void doFirstTry(int);
	void eliminateDoor();
	void doSecondTry(int);

	GameEngineState getState();
	int getNumberOfDoors();
	DoorState getDoorStateByIndex(int index);
	Prize getDoorContentByIndex(int index);

	bool isCarWon();
	void print();
};