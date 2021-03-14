#pragma once

struct rect {
	olc::vi2d pos;
	olc::vi2d size;
};

/// <summary>
/// Which screen to render
/// </summary>
enum class Screen {
	/// <summary>
	/// The menu
	/// </summary>
	Menu,

	/// <summary>
	/// Playing the game
	/// </summary>
	Game,

	/// <summary>
	/// Oh no.. game over screen
	/// </summary>
	GameOver,

	/// <summary>
	/// Show the highscore
	/// </summary>
	Highscore
};