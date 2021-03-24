#include <fstream>
#include "Highscore.h"


Highscore::Highscore(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void Highscore::Init() {
}

void Highscore::Show() {
	globalState->highscoreManager.Load();
	engine->Clear(olc::BLANK);
	engine->DrawString(100, 40, "Highscore!", olc::WHITE);
	
	char formatString[100];
	int yOffset = 50;
	for (int i = 0; i < 10; i++) {
		snprintf(formatString, 100, "%s - %d", globalState->highscoreManager.scores[i].name.c_str(), globalState->highscoreManager.scores[i].score);
		engine->DrawString(100, yOffset, formatString, olc::WHITE);
		yOffset += 10;
	}

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