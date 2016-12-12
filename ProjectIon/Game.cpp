// This Include:
#include "Game.h"

// Local Includes:
#include "BackBuffer.h"
#include "InputHandler.h"
#include "ControllerPlayer.h"
#include "LogManager.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "Physics.h"

// Library Includes:

#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vld.h>


Game* Game::sm_pInstance = 0;
const int WindowWidth = 800;
const int WindowHeight = 600;

const int LEVEL_WIDTH = 1400;
const int LEVEL_HEIGHT = 1050;

const int CAMERA_WIDTH = 800;
const int CAMERA_HEIGHT = 600;

int longTest = 0;


//SDL_Rect camera = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

Game&
Game::GetInstance()
{

	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);
	
	return(*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_pControllerPlayer(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{

}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool
Game::Initialise()
{
	VLDEnable();

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(WindowWidth, WindowHeight))
	{
		LogManager::GetInstance().Log("BackBuffer Init Failed");
		return(false);
	}

	m_pPhysics = new Physics();
	if (!m_pPhysics->Initialise())
	{
		LogManager::GetInstance().Log("Physics Init Failed");
		return (false);
	}

	m_pControllerPlayer = new ControllerPlayer();
	if (!m_pControllerPlayer->Initialise(*m_pBackBuffer, *m_pPhysics))
	{
		LogManager::GetInstance().Log("Player Controller Init Failed");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise(*m_pControllerPlayer))
	{
		LogManager::GetInstance().Log("InputHandler Init Failed");
		return (false);
	}

	m_pLevelManager = new LevelManager();
	m_pLevelManager->PrepareLevel(*m_pBackBuffer, "Assets\\Levels\\Castle2.txt");


	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return(true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput();


	int check = VLDGetLeaksCount();
	if (longTest == 1000)
	{
		//m_looping = false;
	}

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 300.0f;
		m_lastTime = current;
		
		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(deltaTime);

			m_lag -= stepSize;

			++m_numUpdates;
		}

		longTest++;

		Draw(*m_pBackBuffer);
	}
	else
	{
		VLDReportLeaks();
	}

	SDL_Delay(1);
	return(m_looping);
}

void
Game::Process(float deltaTime)
{
	m_elapsedSeconds += deltaTime;

	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Process Game System



	// Player Controller Process
	m_pPhysics->Process(deltaTime);
	
	m_pControllerPlayer->Process(deltaTime, 0, 0);
	//m_pControllerBackground->Process(deltaTime, m_pControllerPlayer->GetPlayer());


	// Process Level
	m_pLevelManager->Process(deltaTime, *m_pControllerPlayer);

	//Adjust Camera

	//AdjustCamera();

	// Do Process



}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;
	backBuffer.Clear();

	//m_pControllerBackground->Draw(backBuffer);
	

	// Level Draw();
	m_pLevelManager->Draw(backBuffer);

	
	// Draw Objects
	m_pControllerPlayer->Draw(backBuffer);

	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::SetBackground(BackBuffer& backBuffer)
{
	//m_pControllerBackground->SetBackgroundMain(backBuffer, "Assets\\Backgrounds\\GrassBackgroundPlain.png");
	//m_pControllerBackground->SetBackgroundLayerBack(backBuffer, "Assets\\Backgrounds\\GrassBackgroundLayer2.png");
	//m_pControllerBackground->SetBackgroundLayerFront(backBuffer, "");
	
}

void
Game::AdjustCamera()
{
	//Player& player = m_pControllerPlayer->GetPlayer();

	//camera.x = (player.GetPositionX() + player.GetWidth() / 2) - CAMERA_WIDTH / 2;
	//camera.y = (player.GetPositionY() + player.GetHeight() / 2) - CAMERA_HEIGHT / 2;

	//if (camera.x < 0)
	//{
	//	camera.x = 0;
	//}
	//if (camera.y < 0)
	//{
	//	camera.y = 0;
	//}
	//if (camera.x > LEVEL_WIDTH - camera.w)
	//{
	//	camera.x = LEVEL_WIDTH - camera.w;
	//}

	//if (camera.y > LEVEL_HEIGHT - camera.h)
	//{
	//	camera.y = LEVEL_HEIGHT - camera.h;
	//}

	//m_pBackBuffer->SetCamera(camera.x, camera.y, camera.w, camera.h);

}
