// This Includes:
#include "InputHandler.h"

// Local Includes:
#include  "ControllerPlayer.h"

// Library Includes

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

bool
InputHandler::Initialise(ControllerPlayer& controllerPlayer)
{
	m_pControllerPlayer = &controllerPlayer;

	return true;
}

void
InputHandler::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				m_pControllerPlayer->MovePlayerUp();
				break;
			case SDLK_s:
				m_pControllerPlayer->MovePlayerDown();
				break;
			case SDLK_a:
				m_pControllerPlayer->MovePlayerLeft();
				break;
			case SDLK_d:
				m_pControllerPlayer->MovePlayerRight();
				break;
			default:
				break;
			}

			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_p:
				m_pControllerPlayer->CenterPlayer();
				break;
			case SDLK_w:
				m_pControllerPlayer->StopPlayerVelocityY();
				break;
			case SDLK_s:
				m_pControllerPlayer->StopPlayerVelocityY();
				break;
			case SDLK_a:
				m_pControllerPlayer->StopPlayerVelocityX();
				break;
			case SDLK_d:
				m_pControllerPlayer->StopPlayerVelocityX();
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}