#pragma once
/// <summary>
///  All the data we must share between screens
/// </summary>
class GameState
{
public:
	int score = 0;
	bool showDebugInformation = false;
	int debugLayer = 0;
};

