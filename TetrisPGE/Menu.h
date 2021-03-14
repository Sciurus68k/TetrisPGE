#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "GameState.h"

/// <summary>
/// Implementation of the menu
/// </summary>
class Menu
{
private:
	olc::PixelGameEngine* engine;
	GameState* globalState;

public:
	Menu(olc::PixelGameEngine* engine, GameState* gameState);
	void Init();
	Screen OnUserUpdate(float fElapsedTime);
	void Hide();
};

