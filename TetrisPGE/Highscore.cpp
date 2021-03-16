#include "Highscore.h"

Highscore::Highscore(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void Highscore::Init() {
}

void Highscore::Show() {
	engine->Clear(olc::BLANK);
	engine->DrawString(200, 80, "Highscore!", olc::WHITE, 2);
	engine->DrawString(200, 100, "1 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 120, "2 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 140, "3 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 160, "4 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 180, "5 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 200, "6 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 220, "7 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 240, "8 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 260, "9 - 1000", olc::WHITE, 2);
	engine->DrawString(200, 280, "10 - 1000", olc::WHITE, 2);

}

void Highscore::Hide() {
	engine->Clear(olc::BLANK);
}

Screen Highscore::OnUserUpdate(float fElapsedTime) {
	if (engine->GetKey(olc::Key::ENTER).bPressed) {
		return Screen::Menu;
	}
	else if (engine->GetKey(olc::Key::SPACE).bPressed) {
		return Screen::Menu;
	}
	else if (engine->GetKey(olc::Key::ESCAPE).bPressed) {
		return Screen::Menu;
	}

	return Screen::Highscore;
}