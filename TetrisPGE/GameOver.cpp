#include "GameOver.h"

GameOver::GameOver(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
}

void GameOver::Init() {
	engine->Clear(olc::BLANK);
	engine->DrawString(50, 0, "GameOver!");
	engine->DrawString(50, 50, "Score: ");
	char score[10];
	snprintf(score, 10, "%d", globalState->score);
	engine->DrawString(50, 100, score, olc::WHITE);
}

void GameOver::Hide() {
	engine->Clear(olc::BLANK);
}

Screen GameOver::OnUserUpdate(float fElapsedTime) {
	if (engine->GetKey(olc::Key::ENTER).bPressed) {
		return Screen::Menu;
	}
	return Screen::GameOver;
}