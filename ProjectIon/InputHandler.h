// 717310 C++ SDL Framework
#ifndef __INPUTHANDLER_H__
#define __INPUTHANDLER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class ControllerPlayer;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise(ControllerPlayer& controllerPlayer);
	void ProcessInput();

	bool CheckMovement();

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	//SDL_Joystick* m_pGameController;

private:
	ControllerPlayer* m_pControllerPlayer;

};

#endif // __INPUTHANDLER_H__
