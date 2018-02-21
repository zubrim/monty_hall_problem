#pragma once
#include <vector>
#include "Observer.h"

class Observable
{
private:
	std::vector<Observer*> observers_;
public:
	Observable();
	~Observable();
	void addObserver(Observer*);
	void notifyUpdate();

};

