#include "GameViewConsole.h"
#include <iostream>
#include <iomanip>

GameViewConsole::GameViewConsole(GameModel& gameModel, GameController& gameController)
	: GameView(gameModel,gameController) {}
GameViewConsole::~GameViewConsole() {};

void GameViewConsole::update() {
	switch (gameModel_.getState()) {
	case GameEngineState::READY: showReady(); break;
	case GameEngineState::FIRST_TRY_DONE: showFirstTryDone(); break;
	case GameEngineState::DOOR_ELIMINATED: showDoorEliminated(); break;
	case GameEngineState::SECOND_TRY_DONE: showSecondTryDone(); break;
	case GameEngineState::QUIT: break;
	}
}
void GameViewConsole::showReady() {
	int pickedDoor;
	system("cls");
	printDoors();
	std::cout << "Enter door number: ";
	std::cin >> pickedDoor;
//	gameController_.doFirstTry(pickedDoor); // event (method invocation) sent to Controller
	gameController_.pickDoorCommand(pickedDoor); // event (method invocation) sent to Controller

};
void GameViewConsole::showFirstTryDone() {
	system("cls");
	printDoors();
	std::cout << "Now one door with the goat will be eliminated." << std::endl;
	system("pause");
//	gameController_.eliminateDoor();
	gameController_.eliminateDoorCommand();
};
void GameViewConsole::showDoorEliminated() {
	int pickedDoor;
	system("cls");
	printDoors();
	std::cout << "Would you like to reconsider your choice? Enter door number: ";
	std::cin >> pickedDoor;
//	gameController_.doSecondTry(pickedDoor); // event (method invocation) sent to Controller
	gameController_.pickDoorCommand(pickedDoor);
};
void GameViewConsole::showSecondTryDone() {
	system("cls");
	printDoors();
	for (int i = 1; i <= gameModel_.getNumberOfDoors(); ++i) {
		std::cout << std::setw(15) << std::left << gameModel_.getDoorContentText(i);
	}
	std::cout << std::endl;
	if (gameModel_.isCarWon()) {
		std::cout << "YOU WON A CAR!" << std::endl;
	}
	else {
		std::cout << "YOU LOST GAME!" << std::endl;
	}
	char choice;
	do {
		std::cout << "Enter Q to quit or N to start a new game: ";
		std::cin >> choice;
	} while (!(choice == 'Q' || choice == 'q' || choice == 'N' || choice == 'n'));
	switch (choice) {
//	case 'Q': case 'q': gameController_.quitChoosen(); break;
//	case 'N': case 'n': gameController_.newGameChoosen(); break;
	case 'Q': case 'q': gameController_.quitGameCommand(); break;
	case 'N': case 'n': gameController_.startNewGameCommand(); break;
	}
};

void GameViewConsole::printDoors() {
	for (int i = 1; i <= gameModel_.getNumberOfDoors(); ++i) {
		std::cout << std::setw(15) << std::left << ("Door " + std::to_string(i));
	}
	std::cout << std::endl;
	for (int i = 1; i <= gameModel_.getNumberOfDoors(); ++i) {
		std::cout << std::setw(15) << std::left << gameModel_.getDoorStateText(i);
	}
	std::cout << std::endl;
}
