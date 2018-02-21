#pragma once
#include "GameView.h"
#include "MainWindow.h"

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/paint/image.hpp>
#include <nana/gui/state_cursor.hpp>
#include  <nana/paint/graphics.hpp>



class GameViewGUI :
	public GameView
{
private:
	std::unique_ptr<MainWindow> mainWindow_;
public:
	GameViewGUI(GameModel& gameModel, GameController& gameController);
	~GameViewGUI();
	virtual void showReady() override;
	virtual void showFirstTryDone() override;
	virtual void showSecondTryDone() override;
	virtual void showDoorEliminated() override;

	virtual void update() override;
};

