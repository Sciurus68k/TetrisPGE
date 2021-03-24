#pragma once

#include "olcPixelGameEngine.h"
#include "Definitions.h"
#include "Tetrominos.h"
#include "GameState.h"

/// <summary>
/// State of a tetromino
/// </summary>
class Piece {
public:
	int index;
	int color;
	int rotation;
	int x;
	int y;

	/// <summary>
	/// Construct a new random piece
	/// </summary>
	Piece() : Piece(rand() % 7, rand() % 4, 0, 0, 0) {
	}

	/// <summary>
	/// Construct a piece
	/// </summary>
	/// <param name="index">Index</param>
	/// <param name="color">Color</param>
	/// <param name="rotation">Rotation</param>
	/// <param name="x">X</param>
	/// <param name="y">Y</param>
	Piece(int index, int color, int rotation, int x, int y) {
		this->index = index;
		this->color = color;
		this->rotation = rotation;
		this->x = x;
		this->y = y;
	}
};


/// <summary>
/// Represents the state of the current game
/// </summary>
struct State {
	unsigned int* field = nullptr;
	bool changed = false;
	std::vector<int> lines;
	Piece* currentPiece = nullptr;
	Piece* nextPiece = nullptr;
	bool forceDown = false;
	bool downUntilLock = false;
	float gameSpeed = 0.5f;
	int pieceCount = 0;
};

/// <summary>
/// Definitions for UI elements
/// </summary>
struct Ui {
	// Layers
	int uiElementsLayer = 0;
	int gameLayer = 0;
	// Positions of some UI elements
	olc::vi2d scorePosition;
	olc::vi2d posNextPiece;

	// The score as a string
	char scoreString[10];
	// Debug text
	char debugInfo[256];

	// Definition of the playing field
	rect field;
	int columns = 12;
	int rows = 18;
	int borderWidth = 1;
	olc::Pixel borderColor = 0xFFA68E24;
	int blockSize = 16;
	olc::vi2d fieldOffset = { 87, 51 };
	int colorTable[4];
	int nextPieceBlockSize = 6;

};

class Tetris
{
private:
	olc::PixelGameEngine* engine;
	State state;
	Ui ui;
	Tetrominos tetrominos;
	void DrawNextPiece();
	int Rotate(int px, int py, int r);
	void NextPiece();
	bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY);
	float accumulatedTime;
	float holdTime;
	GameState* globalState;
	bool bgInitialized = false;

public:
	Tetris(olc::PixelGameEngine* engine, GameState* gameState);
	~Tetris();
	Screen OnUserUpdate(float fElapsedTime);
	void Init();
	void Hide();
	void Show();
};

