#ifndef __CONTROLLER_PLAYER_H__
#define __CONTROLLER_PLAYER_H__


// Local Includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Player.h"
#include "Physics.h"

// Library Includes:


class ControllerPlayer
{
	// Member Methods
public:
	ControllerPlayer();
	~ControllerPlayer();

	bool Initialise(BackBuffer& backBuffer, Physics& physics);

	void Process(float deltaTime, int LevelWidth, int LevelHeight);
	void Draw(BackBuffer& backBuffer);

	Player& GetPlayer();

	void CenterPlayer();
	void MovePlayerRight();
	void MovePlayerLeft();
	void MovePlayerUp();
	void MovePlayerDown();

	void StopPlayerVelocityX();
	void StopPlayerVelocityY();

private:
	bool CreatePlayer(BackBuffer& backBuffer, Physics& physics);
	bool RemovePlayer();
	bool CreatePlayerSprite(BackBuffer& backBuffer);
	void RemovePlayerSprite();

	// Member Data
public:

private:
	Player* m_pPlayer;
	Sprite* m_pPlayerSprite;

};

#endif // __CONTROLLER_PLAYER_H__