// Library includes:
#include <SDL.h>
#include <stdio.h>

// Local includes:
#include "game.h"
#include "logmanager.h"

int main(int argc, char* argv[])
{
	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game Init Failed!");

		return (1);
	}

	while (gameInstance.DoGameLoop())
	{

		// No body.
	}


	Game::DestroyInstance();

	return (0);
}
