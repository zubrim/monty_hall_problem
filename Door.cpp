#pragma once
#include "Door.h"
#include <iostream>
#include <string>


Door::Door(Prize content): content_(content) {}
Door::~Door(){}

void Door::setState(DoorState state) { state_ = state; }
DoorState Door::getState() { return state_; }

Prize Door::getContent() const { return content_; }

void Door::print() const {
	std::string stateText;
	switch (state_) {
		case DoorState::INITIAL: stateText = "INITIAL"; break;
		case DoorState::PICKED: stateText = "PICKED"; break;
		case DoorState::ELIMINATED: stateText = "ELIMINATED"; break;
	}
	std::string contentText;
	switch (content_) {
		case Prize::CAR : contentText = "CAR"; break;
		case Prize::GOAT: contentText = "GOAT"; break;
	}
	std::cout << "Door state: " << stateText << " | "
		<< "Door content: " << contentText << std::endl;
}
