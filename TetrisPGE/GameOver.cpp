#include "GameOver.h"

GameOver::GameOver(olc::PixelGameEngine* engine, GameState* gameState) {
	this->engine = engine;
	this->globalState = gameState;
	for (int i = 0; i < 9; i++) {
		name[i] = 0;
	}
}

void GameOver::Init() {
	for (int i = 0; i < 9; i++) {
		name[i] = 0;
	}
	staticTextLayer = engine->CreateLayer();
}

void GameOver::Show() {
	engine->Clear(olc::BLANK);
	engine->SetDrawTarget(staticTextLayer);
	engine->Clear(olc::BLANK);
	engine->DrawString(200, 80, "GameOver!", olc::WHITE, 2);
	engine->DrawString(200, 100, "Score: ", olc::WHITE, 2);
	
	char score[10];
	snprintf(score, 10, "%d", globalState->score);
	engine->DrawString(200, 120, score, olc::WHITE, 2);

	engine->DrawString(80, 140, "Enter your name and press Enter to continue", olc::WHITE, 2);
	engine->EnableLayer(staticTextLayer, true);
	engine->SetDrawTarget(nullptr);
}

void GameOver::Hide() {
	engine->Clear(olc::BLANK);
	engine->EnableLayer(staticTextLayer, false);
}

Screen GameOver::OnUserUpdate(float fElapsedTime) {
	nameChanged = false;
	if (engine->GetKey(olc::Key::ENTER).bPressed) {
		// Save highscore
		return Screen::Menu;
	}
	
	// Check Key Press only if space for the name is left
	if (nameIdx >= 0 && nameIdx < 8) {
		if (engine->GetKey(olc::Key::A).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'A';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::B).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'B';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::C).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'C';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::D).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'D';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::E).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'E';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::F).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'F';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::G).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'G';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::H).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'H';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::I).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'I';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::J).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'J';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::K).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'K';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::L).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'L';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::M).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'M';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::N).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'N';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::O).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'O';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::P).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'P';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::Q).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'Q';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::R).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'R';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::S).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'S';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::T).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'T';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::U).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'U';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::V).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'V';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::W).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'W';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::X).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'X';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::Y).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'Y';
			nameIdx++;
		}
		else if (engine->GetKey(olc::Key::Z).bPressed) {
			nameChanged = true;
			name[nameIdx] = 'Z';
			nameIdx++;
		}
	}

	if (engine->GetKey(olc::Key::BACK).bPressed) {
		if (nameIdx > 0) {
			nameChanged = true;
			nameIdx--;
			name[nameIdx] = 0;
		}
	}

	if (nameChanged) {
		engine->Clear(olc::BLANK);
		engine->DrawString(200, 160, name, olc::WHITE, 2);
	}

	return Screen::GameOver;
}