#pragma once
#include "GameController.h"
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/audio/player.hpp>
#include <nana/gui/widgets/menubar.hpp>

using namespace nana;

class Formatter {
public:
	static std::function<std::string(std::string)> set(std::string);
};

class MainWindow :
	public form
{
private:
	int gameCount_{ 0 };
	GameController& gameController_;
	std::vector<std::string> imagePaths_ 
	{ "images/closed.png","images/goat.png","images/car.png", "images/background.jpg", "images/green_goat.png" };
	std::vector<std::unique_ptr<paint::image>> images_;
	std::vector<std::unique_ptr<picture>> doors_;
	std::unique_ptr<label> prompt_;
	std::unique_ptr<place> plc_;
	std::unique_ptr<button> eliminateDoorButton_, startNewGameButton_;

	std::function<std::string(std::string)> boldFormatter_, normalFormatter_;

	element::bground bground;
	std::string plc_str_ =
		"vertical <horizontal menubar weight=30>"
		"<horizontal doors weight = 75% margin = [70,20,50,20] gap = 50>"
		"<horizontal prompt margin=[20,10,20,10]>";
	std::string plc_str2_ =
		"vertical <horizontal menubar weight=30>"
		"<horizontal doors weight = 75% margin = [70,20,50,20] gap = 50>"
		"<horizontal <prompt weight=75% margin=[20,50,20,20]>"
		"<vertical margin=[20,50,20,20] <dummy1><button weight=60%><dummy2>>";
	std::string plc_str3_ =
		"vertical <horizontal menubar weight=30>"
		"<horizontal doors weight = 75% margin = [70,20,50,20] gap = 50>"
		"<vertical margin=20 <dummy1><horizontal weight=60% <hdummy1><button weight=60%><hdummy2>><dummy2>>";
	// sounds
	std::unique_ptr<audio::player> bleat_;
	std::unique_ptr<audio::player> tada_;
	std::unique_ptr<audio::player> buttonPush_;
	std::unique_ptr<audio::player> gameShowWheelSpin_;
	menubar menuBar_{ *this };
	void make_menus_();
public:
	MainWindow(GameController& gameController);
	~MainWindow();
	std::vector<std::unique_ptr<picture>>& getDoors() { return doors_; }
	int numberOfDoors() { return 3; }; /// number of doors equals 3 in the first version of program
	GameController& getGameController();
	void setPrompt(std::string caption, int format);
	void renderTheDoorEliminated(int i);
	void renderTheDoorPicked(int i);
	void renderTheDoorOpened(int i);
	void renderPrompt(GameEngineState state);
	void playBleatOrWinSound();
	void reset();
	bool isFirstGame() { return gameCount_ == 0; }
	void incrementGameCount() { ++gameCount_; }
};

