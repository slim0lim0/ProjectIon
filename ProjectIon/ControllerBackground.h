#ifndef __CONTROLLER_BACKGROUND_H__
#define __CONTROLLER_BACKGROUND_H__

// Local Includes:
#include "BackBuffer.h"
#include "Background.h"
#include "Player.h"

class ControllerBackground
{
	//Member Methods

public:
	ControllerBackground();
	~ControllerBackground();

	bool Initialise();

	void Process(float deltaTime);
	void Process(float deltaTime, Player& player);
	void Draw(BackBuffer& backBuffer);

	void SetBackgroundMain(BackBuffer& backBuffer, const char* pcFilename);
	void SetBackgroundLayerBack(BackBuffer& backBuffer, const char* pcFilename);
	void SetBackgroundLayerFront(BackBuffer& backBuffer, const char* pcFilename);
protected:

private:
	void MonitorVelocity(Background& background, Player& player, bool Horizontal, bool Vertical);
	//Member Data
public:

protected:

private:
	Background* m_pBackgroundMainSprite;
	Background* m_pBackgroundLayerBackSprite;
	Background* m_pBackgroundLayerFrontSprite;

};

#endif // __CONTROLLER_BACKGROUND_H__