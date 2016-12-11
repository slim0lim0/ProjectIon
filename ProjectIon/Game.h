
#ifndef __GAME_H__
#define __GAME_H__

class BackBuffer;
class InputHandler;
class ControllerPlayer;
class ControllerBackground;
class LevelManager;
class Physics;

class Game
{
// Member Methods
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void SetBackground(BackBuffer& backBuffer);

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void AdjustCamera();

private:
	Game(const Game& game);
	Game& operator=(const Game& game);

	Game();

// Member Data

public:

protected:
	LevelManager* m_pLevelManager;

	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	ControllerPlayer* m_pControllerPlayer;
	ControllerBackground* m_pControllerBackground;
	Physics* m_pPhysics;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	int m_missileCooldown;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

private:

};

#endif // __GAME_H__