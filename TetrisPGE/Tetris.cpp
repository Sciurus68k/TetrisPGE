#include "Tetris.h"

Tetris::Tetris(olc::PixelGameEngine* engine, GameState* gameState) {
	
	this->engine = engine;
	this->globalState = gameState;

	ui.field.pos.x = 1;
	ui.field.pos.y = 0;
	ui.field.size.x = ui.columns * ui.blockSize;
	ui.field.size.y = ui.rows * ui.blockSize;

	state.field = new unsigned int[ui.columns * ui.rows];

	ui.scorePosition = { ui.field.size.x + 3, 0 };
	ui.posNextPiece = { ui.field.size.x + 3, 10 };

	ui.posFeena.x = ui.field.size.x + 3;
	ui.posFeena.y = 70;

	// Color Table
	ui.colorTable[0] = 0XFFD9C725;
	ui.colorTable[1] = 0xFF38D3F2;
	ui.colorTable[2] = 0xFF2E76F2;
	ui.colorTable[3] = 0xFF3030F2;

	NextPiece();
}

Tetris::~Tetris() {
	delete state.nextPiece;
	delete state.currentPiece;
	delete state.field;
}

// called if the users starts a new game
void Tetris::Init() {
	if (!bgInitialized) {
		ui.gameLayer = engine->CreateLayer();
		ui.bgLayer = engine->CreateLayer();
		engine->SetDrawTarget(ui.bgLayer);

		// Setup the field border
		engine->FillRect(0, ui.field.pos.y, ui.borderWidth, ui.field.size.y + 1, ui.borderColor); // Left Border
		engine->FillRect(ui.field.size.x, 0, ui.borderWidth, ui.field.size.y, ui.borderColor); // Right Border
		engine->FillRect(0, ui.field.size.y, ui.field.size.x + 1, 1, ui.borderColor); // Bottom Border

		// Border for next piece box
		engine->DrawRect(ui.posNextPiece.x, ui.posNextPiece.y, 40, 40, ui.borderColor);
		ui.posNextPiece.x += 2;
		ui.posNextPiece.y += 2;

		for (auto i = 1; i < 12; i++) {
			engine->DrawLine(i * ui.blockSize, 0, i * ui.blockSize, ui.field.size.y, ui.borderColor);
		}

		engine->DrawString(ui.scorePosition, "Score: ");
		ui.scorePosition.x += engine->GetTextSize("Score: ").x;

		engine->SetDrawTarget(nullptr);
		bgInitialized = true;
	}

	state.gameSpeed = 0.5f;
	state.pieceCount = 0;
	engine->EnableLayer(ui.bgLayer, true);
	engine->EnableLayer(ui.gameLayer, true);
	globalState->score = 0;
	memset(&state.field[0], 0, sizeof(state.field) * ui.columns * ui.rows);
	engine->Clear(olc::BLANK);
}

void Tetris::Hide() {
	engine->SetDrawTarget(ui.gameLayer);
	engine->Clear(olc::BLANK);
	engine->SetDrawTarget(nullptr);
	engine->EnableLayer(ui.bgLayer, false);
	engine->EnableLayer(ui.gameLayer, false);
}

Screen Tetris::OnUserUpdate(float fElapsedTime) {
	Screen nextScreen = Screen::Game;
	state.changed = false;

	if (engine->GetKey(olc::Key::SPACE).bPressed) {
		state.forceDown = true;
		state.downUntilLock = true;
	}
	else if (engine->GetKey(olc::Key::UP).bPressed && DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation + 1, state.currentPiece->x, state.currentPiece->y)) {
		state.currentPiece->rotation += 1;
		state.changed = true;
	}
	else if (engine->GetKey(olc::Key::LEFT).bPressed && DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x - 1, state.currentPiece->y)) {
		state.currentPiece->x--;
		state.changed = true;
		holdTime = 0;
	}
	else if (engine->GetKey(olc::Key::RIGHT).bPressed && DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x + 1, state.currentPiece->y)) {
		state.currentPiece->x++;
		state.changed = true;
		holdTime = 0;
	}
	else if (engine->GetKey(olc::Key::DOWN).bPressed) {
		state.forceDown = true;
		holdTime = 0;
	}
	else if (engine->GetKey(olc::Key::DOWN).bHeld) {
		if (holdTime > 0.2) {
			state.forceDown = true;
			holdTime = 0;
		}
		else {
			holdTime += fElapsedTime;
		}
	}
	else if (engine->GetKey(olc::Key::RIGHT).bHeld) {
		if (holdTime > 0.2 && DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x + 1, state.currentPiece->y)) {
			state.currentPiece->x++;
			state.changed = true;
			holdTime = 0;
		}
		else {
			holdTime += fElapsedTime;
		}
	}
	else if (engine->GetKey(olc::Key::LEFT).bHeld) {
		if (holdTime > 0.2 && DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x - 1, state.currentPiece->y)) {
			state.currentPiece->x--;
			state.changed = true;
			holdTime = 0;
		}
		else {
			holdTime += fElapsedTime;
		}
	}

	accumulatedTime += fElapsedTime;
	if (accumulatedTime > state.gameSpeed) {
		state.forceDown = true;
		accumulatedTime = 0;
	}

	if (state.forceDown || state.downUntilLock)
	{
		state.changed = true; // We must rerender the field
		state.forceDown = false;
		if (DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x, state.currentPiece->y + 1)) {
			state.currentPiece->y++; // It can, so do it!
		}
		else
		{
			// It can't! Lock the piece in place
			for (int px = 0; px < 4; px++) {
				for (int py = 0; py < 4; py++) {
					if (tetrominos[state.currentPiece->index][Rotate(px, py, state.currentPiece->rotation)] != L'.') {
						state.field[(state.currentPiece->y + py) * ui.columns + (state.currentPiece->x + px)] = ui.colorTable[state.currentPiece->color];
					}
				}
			}

			// Check if a line is done
			for (int py = 0; py < 4; py++) {
				if (state.currentPiece->y + py < ui.rows)
				{
					bool bLine = true;
					for (int px = 0; px < ui.columns; px++)
						bLine &= (state.field[(state.currentPiece->y + py) * ui.columns + px]) != 0;

					if (bLine)
					{
						// Remove line
						for (int px = 0; px < ui.columns; px++) {
							state.field[(state.currentPiece->y + py) * ui.columns + px] = 0xFFFFFFFF;
						}
						state.lines.push_back(state.currentPiece->y + py);
						globalState->score += 100;
					}
				}
			}

			globalState->score += 25;
			NextPiece();

			if (!DoesPieceFit(state.currentPiece->index, state.currentPiece->rotation, state.currentPiece->x, state.currentPiece->y)) {
				// If piece does not fit straight away, game over!
				nextScreen = Screen::GameOver;
			}
		}
	}

	if (state.changed) {
		engine->SetDrawTarget(ui.gameLayer);
		if (!state.lines.empty())
		{
			for (auto& v : state.lines)
				for (int px = 0; px < ui.columns; px++)
				{
					for (int py = v; py > 0; py--)
						state.field[py * ui.columns + px] = state.field[(py - 1) * ui.columns + px];

					state.field[px] = 0;
				}

			state.lines.clear();
		}

		engine->Clear(olc::BLANK);
		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetrominos[state.currentPiece->index][Rotate(px, py, state.currentPiece->rotation)] != L'.')
					engine->FillRect(state.currentPiece->x * ui.blockSize + (px * ui.blockSize),
						state.currentPiece->y * ui.blockSize + (py * ui.blockSize),
						ui.blockSize,
						ui.blockSize, ui.colorTable[state.currentPiece->color]);

		// Draw field
		for (int x = 0; x < ui.columns; x++) {
			for (int y = 0; y < ui.rows; y++) {
				if (state.field[y * ui.columns + x] > 0) {
					engine->FillRect(x * ui.blockSize, y * ui.blockSize, ui.blockSize, ui.blockSize, state.field[y * ui.columns + x]);
				}
			}
		}

		// Draw Score
		snprintf(ui.scoreString, 10, "%d", globalState->score);
		engine->DrawString(ui.scorePosition, ui.scoreString, olc::WHITE);
		DrawNextPiece();
	}
	
	if (globalState->showDebugInformation) {
		engine->SetDrawTarget(globalState->debugLayer);
		engine->Clear(olc::BLANK);
		snprintf(ui.debugInfo, 255, "Pieces: %d, Speed: %f", state.pieceCount, state.gameSpeed);
		engine->DrawString(0, 180, ui.debugInfo);
	}

	engine->SetDrawTarget(nullptr);
	return nextScreen;
}

void Tetris::DrawNextPiece() {
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
			if (tetrominos[state.nextPiece->index][py * 4 + px] != L'.')
				engine->FillRect(ui.posNextPiece.x + (px * 8), ui.posNextPiece.y + (py * 8), 8, 8, ui.colorTable[state.nextPiece->color]);
}

int Tetris::Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees			// 0  1  2  3
		pi = py * 4 + px;			// 4  5  6  7
		break;						// 8  9 10 11
									//12 13 14 15

	case 1: // 90 degrees			//12  8  4  0
		pi = 12 + py - (px * 4);	//13  9  5  1
		break;						//14 10  6  2
									//15 11  7  3

	case 2: // 180 degrees			//15 14 13 12
		pi = 15 - (py * 4) - px;	//11 10  9  8
		break;						// 7  6  5  4
									// 3  2  1  0

	case 3: // 270 degrees			// 3  7 11 15
		pi = 3 - py + (px * 4);		// 2  6 10 14
		break;						// 1  5  9 13
	}								// 0  4  8 12

	return pi;
}

void Tetris::NextPiece()
{
	if (state.nextPiece != nullptr) {
		delete state.currentPiece;
		state.currentPiece = state.nextPiece;
		state.nextPiece = new Piece();
	}
	else {
		// First time 
		state.currentPiece = new Piece();
		state.nextPiece = new Piece();
	}

	state.currentPiece->x = 4;
	state.downUntilLock = false;
	state.changed = true;
	state.pieceCount++;
	if (state.pieceCount % 50 == 0 && state.gameSpeed > 0.20) {
		state.gameSpeed -= 0.05f;
	}
}

bool Tetris::DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	// All Field cells >0 are occupied
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them

			if (tetrominos[nTetromino][pi] != L'.')
			{
				if (nPosX + px == ui.columns || nPosX + px < 0)
					return false; // fail on first hit
				if (nPosY + py == ui.rows)
					return false;

				// Get index into field
				int fi = (nPosY + py) * ui.columns + (nPosX + px);

				if (state.field[fi] != 0)
					return false;
			}
		}

	return true;
}