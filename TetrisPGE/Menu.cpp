#include "Menu.h"

Menu::Menu(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void Menu::Init() {
}

void Menu::Show() {
	engine->DrawString(200, 80, "Hello!", olc::WHITE, 2);
	engine->DrawString(200, 120, "Enter = Start Game", olc::WHITE, 2);
	engine->DrawString(200, 160, "Space = Highscore", olc::WHITE, 2);
	engine->DrawString(200, 200, "ESC = Exit", olc::WHITE, 2);
}

void Menu::Hide() {
	engine->Clear(olc::BLANK);
}

Screen Menu::OnUserUpdate(float fElapsedTime) {
	if (engine->GetKey(olc::Key::ENTER).bPressed) {
		return Screen::Game;
	}
	else if (engine->GetKey(olc::Key::SPACE).bPressed) {
		return Screen::Highscore;
	}
	else if (engine->GetKey(olc::Key::ESCAPE).bPressed) {
		return Screen::Exit;
	}

	return Screen::Menu;
}