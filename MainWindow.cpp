#include "MainWindow.h"

std::function<std::string(std::string)> Formatter::set(std::string tags) {
	{
		return [tags](std::string text)->std::string {return "< " + tags + " >" + text + "</>"; };
	}
}

MainWindow::MainWindow(GameController& gameController) :
	form(nana::API::make_center(800, 600), appear::decorate<appear::minimize, appear::taskbar>()),
	gameController_(gameController)
{
	API::window_icon_default(paint::image("monty_hall_problem.exe"));
	API::window_icon(*this, paint::image("icons/green_goat.ico"));
	this->caption("The Monty Hall Problem");

	/// sounds
	bleat_ = std::make_unique<audio::player>("sounds/bleat.wav");
	tada_ = std::make_unique<audio::player>("sounds/tada.wav");
	buttonPush_ = std::make_unique<audio::player>("sounds/button_push.wav");
	gameShowWheelSpin_ = std::make_unique<audio::player>("sounds/game_show_wheel_spin.wav");

	/// define layout
	plc_ = std::make_unique<place>(*this);
	plc_->div(plc_str_.c_str());

	/// set menu bar
	make_menus_();
	plc_->field("menubar") << menuBar_;

	/// set text formatters
	boldFormatter_ = Formatter::set("bold color=0x0066ff font=\"Segoe Print\" size=14");
	normalFormatter_ = Formatter::set("color=0x0066ff font=\"Segoe Print\" size=12");

	/// construct prompt label
	prompt_ = std::make_unique<label>(*this);
	prompt_->caption(boldFormatter_("Pick a door!"));
	prompt_->format(true);
	prompt_->text_align(align::center);
	prompt_->fgcolor(color_rgb(0xFFFFFF));
	API::effects_bground(*prompt_, effects::bground_transparent(0), 0);
	plc_->field("prompt") << *prompt_;


	/// construct door pictures objects
	for (int i = 0; i < imagePaths_.size(); ++i) {
		images_.push_back(std::make_unique<paint::image>(imagePaths_[i]));
	}

	/// construct door objects (nana pictures)
	for (int i = 0; i < numberOfDoors(); ++i) {
		doors_.push_back(std::make_unique<picture>(*this,true));
		doors_[i]->stretchable(10,10,10,10);
		doors_[i]->cursor(cursor::hand);
		doors_[i]->load(*images_[0]); /// load closed door image
		plc_->field("doors") << *doors_[i];
		API::effects_bground(*doors_[i], effects::bground_transparent(0), 0);
		API::effects_bground(*doors_[i], effects::bground_blur(0), 0);
		/// register event handlers on the doors
		doors_[i]->events().click([this, i] {
			this->getGameController().pickDoorCommand(i+1); }); //door numbering starts from 1
	}
	/// make layout effective
	plc_->collocate();

	/// construct eliminate door button
	eliminateDoorButton_ = std::make_unique<button>(*this, "Eliminate door!");
	eliminateDoorButton_->events().click([this] {
		buttonPush_->play();
		gameController_.eliminateDoorCommand(); });
	eliminateDoorButton_->icon(*images_[4]);
	bground.image(paint::image("images/backgroundOfButtons2.png"), true, {});
	eliminateDoorButton_->set_bground(bground);
	/// construct "start new game" button
	startNewGameButton_ = std::make_unique<button>(*this, "Start new game!");
	startNewGameButton_->events().click([this] {
		gameShowWheelSpin_->play();
		gameController_.startNewGameCommand(); });
	startNewGameButton_->set_bground(bground);

	/// draw background
	drawing{ *this }.draw([this](nana::paint::graphics& graph) {
		this->images_[3]->stretch(rectangle{ this->images_[3]->size() }, graph, rectangle{ graph.size() });
	});

	/// event handler on exit
	events().unload([this](const arg_unload& arg) {
		nana::msgbox m(arg.window_handle, "Confirm close", nana::msgbox::yes_no);
		m.icon(m.icon_question);
		m << "Are you sure you want to exit the game?";
		arg.cancel = (m() != m.pick_yes);
		if (!arg.cancel) gameController_.quitGameCommand();
	});
}

void MainWindow::reset() {
	/// reset doors
	for (int i = 0; i < numberOfDoors(); ++i) {
		doors_[i]->load(*images_[0]); /// load closed door image
		doors_[i]->cursor(cursor::hand);
		API::effects_bground(*doors_[i], effects::bground_transparent(0), 0);
		API::effects_bground(*doors_[i], effects::bground_blur(0), 0);
	}

	/// reset prompt
	plc_->erase(*startNewGameButton_);
	startNewGameButton_->hide();
	prompt_->caption(boldFormatter_("Pick a door!"));
	plc_->field("prompt") << *prompt_;
	plc_->div(plc_str_.c_str());
	plc_->collocate();
	prompt_->show();
}

GameController& MainWindow::getGameController() { return gameController_; };
void MainWindow::setPrompt(std::string caption, int format) {
	switch (format) {
	case 0: prompt_->caption(normalFormatter_(caption)); break;
	case 1: default: prompt_->caption(boldFormatter_(caption)); break;
	}
}


void MainWindow::renderTheDoorPicked(int i) {
	API::effects_bground(*doors_[i], effects::bground_blur(12), 0.5);
	plc_->collocate();
};
void MainWindow::renderTheDoorEliminated(int i) {
	doors_[i]->load(*images_[1]);
	API::effects_bground(*doors_[i], effects::bground_transparent(10), 0.5);
	doors_[i]->cursor(cursor::arrow);
	plc_->collocate();
};
void MainWindow::renderTheDoorOpened(int i) {
	int img;
	gameController_.isWin() ? img = 2 : img = 1;
	doors_[i]->load(*images_[img]);
	API::effects_bground(*doors_[i], effects::bground_transparent(0), 0);
	API::effects_bground(*doors_[i], effects::bground_blur(0), 0);
	plc_->collocate();
};

void MainWindow::playBleatOrWinSound() {
	if (gameController_.isWin())
	{
		tada_->play();
	}
	else
	{
		bleat_->play();
	};
}

void MainWindow::renderPrompt(GameEngineState state) {
	static std::string s1{ "Pick door!" };
	static std::string s2{ "Now one door with the goat will be eliminated! Press the button at the right." };
	static std::string s3{ "Would you like to reconsider your choice? Pick door!" };
	static std::string s4{ "Start new game" };


	switch (state) {
	case GameEngineState::READY: 
		plc_->erase(*startNewGameButton_);
		startNewGameButton_->hide();
		prompt_->caption(boldFormatter_(s1));
		plc_->field("prompt") << *prompt_;
		break;
	case GameEngineState::FIRST_TRY_DONE:
		prompt_->caption(boldFormatter_(s2));
		plc_->div(plc_str2_.c_str());
		plc_->field("button") << *eliminateDoorButton_;
		break;
	case GameEngineState::DOOR_ELIMINATED:
		prompt_->caption(boldFormatter_(s3));
		plc_->erase(*eliminateDoorButton_);
		eliminateDoorButton_->hide();
		plc_->div(plc_str_.c_str());
		break;
	case GameEngineState::SECOND_TRY_DONE: 
		plc_->erase(*prompt_);
		prompt_->hide();
		plc_->div(plc_str3_.c_str());
		plc_->field("button") << *startNewGameButton_;
		break;
	default: break;
	}
	plc_->collocate();
};
MainWindow::~MainWindow()
{
}

void MainWindow::make_menus_()
{
	/// menubar appearance
	menuBar_.bgcolor(color_rgb(0xb85c2b));
	API::effects_bground(menuBar_, effects::bground_blur(0), 0.0);
	API::effects_bground(menuBar_, effects::bground_transparent(0), 0.3);

	/// menubar elements
	menuBar_.push_back("&File");
	menuBar_.at(0).append("Exit", [this](menu::item_proxy& ip) {
		nana::API::exit_all();
	});
	menuBar_.push_back("&Settings");
	menuBar_.at(1).append("Language", [this](menu::item_proxy& ip)
	{

	});


	menuBar_.at(1).check_style(0, menu::checks::highlight);

	menuBar_.push_back("&Window");
	menuBar_.at(2).append("About", [this](menu::item_proxy& ip)
	{
		msgbox m(*this, "About program", msgbox::ok);
		m.icon(m.icon_information);
		m << "Author: zubrim [at] kashkan.info\n" << "Copyright 2018";
		m.show();

	});

}