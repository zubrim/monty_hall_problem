#include "GameViewGUI.h"



GameViewGUI::GameViewGUI(GameModel& gameModel, GameController& gameController) :
	GameView(gameModel,gameController)
{
	mainWindow_ = std::make_unique<MainWindow>(gameController);
}

GameViewGUI::~GameViewGUI() { }

void GameViewGUI::showReady() {
	/// show window
	if (mainWindow_->isFirstGame()) {
		mainWindow_->incrementGameCount();
		mainWindow_->show();
		nana::exec();
	}	else {
		mainWindow_->reset();
		mainWindow_->incrementGameCount();
	}

}

void GameViewGUI::showFirstTryDone() {
	/// make the picked door prominent
	for (int i = 0; i < gameModel_.getNumberOfDoors(); ++i) {
		if (gameModel_.getDoorState(i + 1) == DoorState::PICKED) {
			mainWindow_->renderTheDoorPicked(i);
			break;
		}
	}
	/// change command prompt
	mainWindow_->renderPrompt(GameEngineState::FIRST_TRY_DONE);
};

void GameViewGUI::showDoorEliminated() {
	/// reveal the content of the eliminated door
	for (int i = 0; i < gameModel_.getNumberOfDoors(); ++i) {
		if (gameModel_.getDoorState(i + 1) == DoorState::ELIMINATED) {
			mainWindow_->renderTheDoorEliminated(i);
			break;
		}
	}
	/// change command prompt
	mainWindow_->renderPrompt(GameEngineState::DOOR_ELIMINATED);
};


void GameViewGUI::showSecondTryDone() {
	/// reveal the content of the picked door
	for (int i = 0; i < gameModel_.getNumberOfDoors(); ++i) {
		if (gameModel_.getDoorState(i + 1) == DoorState::PICKED) {
			mainWindow_->renderTheDoorOpened(i);
			break;
		}
	}
	/// change command prompt
	mainWindow_->renderPrompt(GameEngineState::SECOND_TRY_DONE);
	mainWindow_->playBleatOrWinSound();

};


void GameViewGUI::update() {
	switch (gameModel_.getState()){
		case GameEngineState::READY: showReady(); break;
		case GameEngineState::FIRST_TRY_DONE: showFirstTryDone(); break;
		case GameEngineState::DOOR_ELIMINATED: showDoorEliminated(); break;
		case GameEngineState::SECOND_TRY_DONE: showSecondTryDone(); break;
		case GameEngineState::QUIT: nana::API::exit_all(); break;
		default: break;
	}
};
