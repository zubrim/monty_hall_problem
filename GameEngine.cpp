#pragma once
#include "GameEngine.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>



GameEngine::GameEngine()
{
	// set seed for random number generator
	seed_ = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	rand_gen_.seed(seed_);

	// create doors with ONE car and goats
	doors_.push_back(Door(Prize::CAR));
	for (int i = 1; i < numDoors_; ++i) {
		doors_.push_back(Door(Prize::GOAT));
	}
	state_ = GameEngineState::INIT;
}

void GameEngine::reset()
{
	// close all doors for the new game
	for_each(begin(doors_), end(doors_), [](Door &door) { door.setState(DoorState::INITIAL); });

	shuffle(begin(doors_), end(doors_), rand_gen_);
	state_ = GameEngineState::READY;
}

void GameEngine::quit() {
	state_ = GameEngineState::QUIT;
}

GameEngine::~GameEngine(){}

GameEngineState GameEngine::getState() {
	return state_;
}

void GameEngine::doFirstTry(int index) {
	Door* pickedDoor = getDoorByIndex_(index);
	pickedDoor->setState(DoorState::PICKED);
	initiallyPickedDoor_ = pickedDoor;
	state_ = GameEngineState::FIRST_TRY_DONE;
}
void GameEngine::eliminateDoor() {
	// compute random door number to eliminate
	int k = (initiallyPickedDoor_->getContent() == Prize::GOAT) ? numDoors_ - 2 : numDoors_ - 1;
	int m = static_cast<int>(real_rand_gen_(rand_gen_)*k);

	auto it = find_if(begin(doors_), end(doors_), [](Door& door) {
		return (door.getContent() == Prize::GOAT) && (door.getState() != DoorState::PICKED); });
	for (int i = 0; i < m ; ++i){
		it = find_if(++it, end(doors_), [](Door& door) {
			return (door.getContent() == Prize::GOAT) && (door.getState() != DoorState::PICKED); });
	}
	eliminatedDoor_ = &(*it);
	eliminatedDoor_->setState(DoorState::ELIMINATED);
	state_ = GameEngineState::DOOR_ELIMINATED;
}
void GameEngine::doSecondTry(int index) {
	Door* pickedDoor = getDoorByIndex_(index);
	initiallyPickedDoor_->setState(DoorState::INITIAL);
	pickedDoor->setState(DoorState::PICKED);
	finallyPickedDoor_ = pickedDoor;
	state_= GameEngineState::SECOND_TRY_DONE;
}

Door* GameEngine::getDoorByIndex_(int index) {
	// doors are labelled from 1 to numDoors_
	return &doors_[index - 1];
}

int GameEngine::getNumberOfDoors() {
	return numDoors_;
}

DoorState GameEngine::getDoorStateByIndex(int index) {
	return doors_[index - 1].getState();
};
Prize GameEngine::getDoorContentByIndex(int index) {
	return doors_[index - 1].getContent();
};

bool GameEngine::isCarWon() {
	bool result = false;
	if (finallyPickedDoor_->getContent() == Prize::CAR) result = true;
	return result;
}

void GameEngine::print() {
	for_each(begin(doors_), end(doors_), [](Door& door) {door.print(); });
	std::string stateText;
	switch (state_) {
		case GameEngineState::READY           : stateText = "READY"; break;
		case GameEngineState::FIRST_TRY_DONE  : stateText = "FIRST_TRY_DONE"; break;
		case GameEngineState::DOOR_ELIMINATED : stateText = "DOOR_ELIMINATED"; break;
		case GameEngineState::SECOND_TRY_DONE : stateText = "SECOND_TRY_DONE"; break;
	}
	std::cout << "Game state: " << stateText << std::endl;
}
