#include "Menu.h"

Menu::Menu(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void Menu::Init() {
	engine->DrawString(50, 0, "Hello!");
	engine->DrawString(50, 20, "Press Enter to");
	engine->DrawString(50, 40, "start the game");
}

void Menu::Hide() {
	engine->Clear(olc::BLANK);
}

Screen Menu::OnUserUpdate(float fElapsedTime) {
	if (engine->GetKey(olc::Key::ENTER).bPressed) {
		return Screen::Game;
	}
	return Screen::Menu;
}