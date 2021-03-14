#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "GameState.h"

/// <summary>
/// Implementation of the GameOver Screen
/// </summary>
class GameOver
{
private:
	olc::PixelGameEngine* engine;
	GameState* globalState;

public:
	GameOver(olc::PixelGameEngine* engine, GameState* gameState);
	void Init();
	Screen OnUserUpdate(float fElapsedTime);
	void Hide();
};