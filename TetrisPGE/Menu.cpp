#include "Menu.h"

Menu::Menu(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void Menu::Init() {
}

void Menu::Show() {
	engine->DrawString(100, 40, "Hello!", olc::WHITE);
	engine->DrawString(100, 60, "Enter = Start Game", olc::WHITE);
	engine->DrawString(100, 80, "Space = Highscore", olc::WHITE);
	engine->DrawString(100, 100, "ESC = Exit", olc::WHITE);
	engine->DrawString(5, 360, "Credits:", olc::WHITE);
	engine->DrawString(5, 370, "Background by Kenney <https://kenney.nl>", olc::WHITE);
	engine->DrawString(5, 380, "PGE by javidx9 <https://OneLoneCoder.com>", olc::WHITE);
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