#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "Menu.h"
#include "Tetris.h"
#include "GameOver.h"

class Game : public olc::PixelGameEngine {
private:
	GameState* gameState;
	Menu* menu;
	Tetris* tetris;
	GameOver* gameOver;
	Screen currentScreen = Screen::Menu;
	
public:
	Game();
	~Game();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void SwitchScreen(Screen newScreen);
};