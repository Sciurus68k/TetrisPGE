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
	int nameIdx = 0;
	char name[9];
	bool nameChanged = false;
	int staticTextLayer = 0;

public:
	GameOver(olc::PixelGameEngine* engine, GameState* gameState);
	void Init();
	Screen OnUserUpdate(float fElapsedTime);
	void Show();
	void Hide();
	
};