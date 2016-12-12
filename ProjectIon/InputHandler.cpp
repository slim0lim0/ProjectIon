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
			{
				SDL_Keycode event = e.key.keysym.sym;
				if (event == SDLK_w)
				{
					m_pControllerPlayer->MovePlayerUp();
					break;
				}
				if (event == SDLK_s)
				{
					m_pControllerPlayer->MovePlayerDown();
					break;
				}
				if (event == SDLK_a)
				{
					m_pControllerPlayer->MovePlayerLeft();
					break;
				}
				if (event == SDLK_d)
				{
					m_pControllerPlayer->MovePlayerRight();
					break;
				}
			}
			case SDL_KEYUP:
			{
				SDL_Keycode event = e.key.keysym.sym;
				if (event == SDLK_w || event == SDLK_s)
				{
					m_pControllerPlayer->StopPlayerVelocityY();
					break;
				}
				if ((event == SDLK_a || event == SDLK_d))
				{
					if (!CheckMovement())
						m_pControllerPlayer->StopPlayerVelocityX();
					break;	
				}
				if (event == SDLK_p)
				{
					m_pControllerPlayer->CenterPlayer();
					break;
				}
			}
			default:
			{
				e.key.keysym.sym = 0;
				break;
			}		
		}
	}
}

bool
InputHandler::CheckMovement()
{
	if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])
	{
		m_pControllerPlayer->MovePlayerLeft();
		return true;
	}
	else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])
	{
		m_pControllerPlayer->MovePlayerRight();
		return true;
	}
	else
		return false;
}