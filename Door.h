#pragma once
enum class DoorState {INITIAL, PICKED, ELIMINATED};
enum class Prize { GOAT, CAR };

class Door
{
private:
	DoorState state_ { DoorState::INITIAL };
	Prize content_;
public:
	Door(Prize);
	~Door();
	void setState(DoorState);
	DoorState getState();
	Prize getContent() const;
	void print() const;
};