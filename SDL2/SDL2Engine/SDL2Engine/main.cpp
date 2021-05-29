#pragma region project include
#include "Engine.h"
#include "Game.h"
#pragma endregion

/// <summary>
/// main entry of engine
/// </summary>
/// <returns>shutdown code</returns>
int main()
{
	// shut down result
	int result;

	// init engine and load images
	if ((result = ENGINE->Init()) == 0 && !(result = ENGINE->Load()))
	{
		// initialize game
		GAME->Init();

		// run engine
		ENGINE->Run();
	}

	// clean game
	GAME->Clean();

	// clean engine
	ENGINE->Clean();

	// return result
	return result;
}