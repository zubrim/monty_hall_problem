#pragma once
#include "Observable.h"
#include <algorithm>



Observable::Observable()
{
}


Observable::~Observable()
{
}

void Observable::addObserver(Observer* observer) {
	observers_.push_back(observer);
}

void Observable::notifyUpdate() {
	for_each(begin(observers_), end(observers_), [](Observer *observer) { observer->update(); });
}
