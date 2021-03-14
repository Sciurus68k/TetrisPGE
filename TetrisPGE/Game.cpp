#include "Game.h"

Game::Game()
{
	// Name your application
	sAppName = "Tetris";

	// Initialize everything
	// No need to keep all screens always in memory. But we should have enough RAM, so why not?
	gameState = new GameState();
	menu = new Menu(this, gameState);
	tetris = new Tetris(this, gameState);
	gameOver = new GameOver(this, gameState);

}

Game::~Game() {
	delete menu;
	delete tetris;
	delete gameOver;
	delete gameState;
}

bool Game::OnUserCreate()
{
	gameState->debugLayer = CreateLayer();
	EnableLayer(gameState->debugLayer, gameState->showDebugInformation);
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
	default:
		break;
	}

	// Init the new screen
	switch (newScreen) {
	case Screen::Menu:
		menu->Init();
		break;
	case Screen::Game:
		tetris->Init();
		break;
	case Screen::GameOver:
		gameOver->Init();
		break;
	default:
		break;
	}

	currentScreen = newScreen;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	if (GetKey(olc::Key::D).bPressed) {
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
		break;
	}

	if (nextScreen != currentScreen) {
		SwitchScreen(nextScreen);
	}

	return true;
}