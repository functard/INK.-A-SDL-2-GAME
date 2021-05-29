#pragma once
#include "Engine.h"

#pragma region forward decleration
class CFont;
#pragma endregion

#pragma region value macro
#define GAME GGame::Get()
#pragma endregion

/// <summary>
/// game class for game logic 
/// </summary>
class GGame
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GGame() {}

	/// <summary>
	/// destructor
	/// </summary>
	~GGame() {}
#pragma endregion

#pragma region public variable
	/// <summary>
	/// arial font
	/// </summary>
	CFont* m_PArial = nullptr;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get game
	/// </summary>
	/// <returns>game</returns>
	inline static GGame* Get()
	{
		// create game if not exists
		static GGame* pGame = new GGame();

		// return game
		return pGame;
	}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize game
	/// </summary>
	void Init();


	void QuitGame()
	{
		ENGINE->Stop();
	}


	/// <summary>
	/// clean game
	/// </summary>
	void Clean();
#pragma endregion
};