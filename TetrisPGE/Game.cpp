#include "Game.h"

Game::Game()
{
	// Name your application
	sAppName = "Tetris";
}

Game::~Game() {
	delete menu;
	delete tetris;
	delete gameOver;
	delete gameState;
	delete highscore;
}

bool Game::OnUserCreate()
{
	// Initialize everything
	gameState = new GameState();
	menu = new Menu(this, gameState);
	tetris = new Tetris(this, gameState);
	gameOver = new GameOver(this, gameState);
	highscore = new Highscore(this, gameState);

	// Now init all the screens to setup their layers
	menu->Init();
	tetris->Init();
	gameOver->Init();
	highscore->Init();

	bgSprite = std::make_unique<olc::Sprite>("assets/backgroundCastles.png");
	bgDecal = std::make_unique<olc::Decal>(bgSprite.get());
	
	Clear(olc::BLANK);
	gameState->debugLayer = CreateLayer();
	SetDrawTarget(gameState->debugLayer);
	Clear(olc::BLANK);
	SetDrawTarget(nullptr);
	EnableLayer(gameState->debugLayer, gameState->showDebugInformation);
	
	bgLayer = CreateLayer();
	EnableLayer(bgLayer, true);
	SwitchScreen(Screen::Menu);
	return true;
}

void Game::SwitchScreen(Screen newScreen) {
	// Call hide on the old screen
	switch (currentScreen) {
	case Screen::Menu:
		menu->Hide();
		break;
	case Screen::Game:
		tetris->Hide();
		break;
	case Screen::GameOver:
		gameOver->Hide();
		break;
	case Screen::Highscore:
		highscore->Hide();
		break;
	default:
		break;
	}

	// Init the new screen
	switch (newScreen) {
	case Screen::Menu:
		menu->Show();
		break;
	case Screen::Game:
		tetris->Show();
		break;
	case Screen::GameOver:
		gameOver->Show();
		break;
	case Screen::Highscore:
		highscore->Show();
		break;
	default:
		break;
	}

	currentScreen = newScreen;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	if (GetKey(olc::Key::HOME).bPressed) {
		gameState->showDebugInformation = !gameState->showDebugInformation;
		EnableLayer(gameState->debugLayer, gameState->showDebugInformation);
	}
	
	Screen nextScreen = currentScreen;
	switch (currentScreen) {
	case Screen::GameOver:
		nextScreen = gameOver->OnUserUpdate(fElapsedTime);
		break;
	case Screen::Game:
		nextScreen = tetris->OnUserUpdate(fElapsedTime);
		break;
	case Screen::Menu:
		nextScreen = menu->OnUserUpdate(fElapsedTime);
		if (nextScreen == Screen::Exit) return false;
		break;
	case Screen::Highscore:
		nextScreen = highscore->OnUserUpdate(fElapsedTime);
		break;
	}

	if (nextScreen != currentScreen) {
		SwitchScreen(nextScreen);
	}
	SetDrawTarget(bgLayer);
	DrawDecal(bgPos, bgDecal.get());
	SetDrawTarget(nullptr);
	return true;
}