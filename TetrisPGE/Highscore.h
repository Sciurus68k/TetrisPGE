#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "GameState.h"


class Highscore
{
private:
	olc::PixelGameEngine* engine;
	GameState* globalState;

public:
	Highscore(olc::PixelGameEngine* engine, GameState* gameState);
	void Init();
	Screen OnUserUpdate(float fElapsedTime);
	void Show();
	void Hide();
};

