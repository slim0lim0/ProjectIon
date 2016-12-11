// This Include:
#include "ControllerPlayer.h"

// Local Includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "LogManager.h"
#include "Physics.h"
// Library Includes:

static const float m_playerSpeed = 800.0;

static const bool m_playerCameraControlled = false;

static const bool m_playerCameraTrack = true;

ControllerPlayer::ControllerPlayer()
: m_pPlayer(0)
{

}

ControllerPlayer::~ControllerPlayer()
{
	if (!RemovePlayer())
	{
		LogManager::GetInstance().Log("Player Deletion Failed");
	}
}

bool
ControllerPlayer::Initialise(BackBuffer& backBuffer, Physics& physics)
{
	if(!CreatePlayer(backBuffer, physics))
	{
		LogManager::GetInstance().Log("Player Controller Init Failed");
		return(false);
	}

	return true;
}

Player&
ControllerPlayer::GetPlayer()
{
	return(*m_pPlayer);
}

void
ControllerPlayer::Process(float deltaTime, int LevelWidth, int LevelHeight)
{
	if (m_pPlayer != 0)
	{
		m_pPlayer->Process(deltaTime, LevelWidth, LevelHeight);
	}
}

void
ControllerPlayer::Draw(BackBuffer& backBuffer)
{
	if (m_pPlayer != 0)
	{
		m_pPlayer->Draw(backBuffer, m_playerCameraControlled, m_playerCameraTrack);
	}
}

bool
ControllerPlayer::CreatePlayer(BackBuffer& backBuffer, Physics& physics)
{
	if (!CreatePlayerSprite(backBuffer))
	{
		LogManager::GetInstance().Log("Player Sprite Init Failed");
		return(false);
	}

	m_pPlayer = new Player();
	if(!m_pPlayer->Initialise(m_pPlayerSprite))
	{
		LogManager::GetInstance().Log("Player Init Failed");
		return(false);
	}

	m_pPlayer->SetBody(physics.CreatePlayer());

	return(true);
}

bool
ControllerPlayer::RemovePlayer()
{
	if (m_pPlayer != 0)
	{
		delete m_pPlayer;
		m_pPlayer = 0;
	}

	return true;
}

bool
ControllerPlayer::CreatePlayerSprite(BackBuffer& backBuffer)
{
	m_pPlayerSprite = backBuffer.CreateSprite("Assets\\Sprites\\Player.png");

	return true;
}

void
ControllerPlayer::RemovePlayerSprite()
{

}

void 
ControllerPlayer::CenterPlayer()
{
	m_pPlayer->SetPositionX(100);
	m_pPlayer->SetPositionY(100);
}

void
ControllerPlayer::MovePlayerRight()
{
	m_pPlayer->SetHorizontalVelocity(m_playerSpeed);
}

void
ControllerPlayer::MovePlayerLeft()
{
	m_pPlayer->SetHorizontalVelocity(-(m_playerSpeed));
}

void
ControllerPlayer::MovePlayerDown()
{
	m_pPlayer->SetVerticalVelocity(m_playerSpeed);
}

void
ControllerPlayer::MovePlayerUp()
{
	m_pPlayer->SetVerticalVelocity(-(m_playerSpeed));
}

void
ControllerPlayer::StopPlayerVelocityX()
{
	m_pPlayer->SetHorizontalVelocity(0);
}

void
ControllerPlayer::StopPlayerVelocityY()
{
	m_pPlayer->SetVerticalVelocity(0);
}