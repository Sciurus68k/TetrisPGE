#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "Menu.h"
#include "Tetris.h"
#include "GameOver.h"
#include "Highscore.h"

class Game : public olc::PixelGameEngine {
private:
	GameState* gameState;
	Menu* menu;
	Tetris* tetris;
	GameOver* gameOver;
	Highscore* highscore;

	Screen currentScreen = Screen::Menu;
	
	int bgLayer;
	const olc::vi2d bgPos = { 0,0 };
	std::unique_ptr<olc::Sprite> bgSprite;
	std::unique_ptr<olc::Decal> bgDecal;

public:
	Game();
	~Game();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void SwitchScreen(Screen newScreen);
};