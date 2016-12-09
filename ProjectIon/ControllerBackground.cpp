//This Include:
#include "ControllerBackground.h"

//Local Includes:
#include "BackBuffer.h"
#include "Sprite.h"
#include "Player.h"

static const bool IsCameraControlled = false;
static const bool IsCameraTrack = false;

static const float Layer2VelocityX = 200;
static const float Layer2VelocityY = 100;


ControllerBackground::ControllerBackground()
: m_pBackgroundMainSprite(0)
, m_pBackgroundLayerBackSprite(0)
, m_pBackgroundLayerFrontSprite(0)
{

}

ControllerBackground::~ControllerBackground()
{
	delete m_pBackgroundMainSprite;
	m_pBackgroundLayerBackSprite = 0;

	delete m_pBackgroundLayerBackSprite;
	m_pBackgroundLayerBackSprite = 0;

	delete m_pBackgroundLayerFrontSprite;
	m_pBackgroundLayerFrontSprite = 0;
}

bool
ControllerBackground::Initialise()
{


	return true;
}

void
ControllerBackground::Process(float deltaTime)
{
	if (m_pBackgroundMainSprite != 0)
		m_pBackgroundMainSprite->Process(deltaTime);


	if (m_pBackgroundLayerBackSprite != 0)
	{
		m_pBackgroundLayerBackSprite->Process(deltaTime);
	}

	if (m_pBackgroundLayerFrontSprite != 0)
		m_pBackgroundLayerFrontSprite->Process(deltaTime);
}

void
ControllerBackground::Process(float deltaTime, Player& player)
{
	if (m_pBackgroundMainSprite != 0)
		m_pBackgroundMainSprite->Process(deltaTime);


	if (m_pBackgroundLayerBackSprite != 0)
	{
		bool bHorizontal = false;
		bool bVertical= false;

		if (Layer2VelocityX != 0)
		{
			bHorizontal = true;
		}
		if (Layer2VelocityY != 0)
		{
			bVertical = true;
		}
			
		MonitorVelocity(*m_pBackgroundLayerBackSprite, player, bHorizontal, bVertical);
		m_pBackgroundLayerBackSprite->Process(deltaTime);
	}

	if (m_pBackgroundLayerFrontSprite != 0)
		m_pBackgroundLayerFrontSprite->Process(deltaTime);
}

void
ControllerBackground::Draw(BackBuffer& backBuffer)
{
	if (m_pBackgroundMainSprite != 0)
		m_pBackgroundMainSprite->Draw(backBuffer, IsCameraControlled, IsCameraTrack);
	if (m_pBackgroundLayerBackSprite != 0)
		m_pBackgroundLayerBackSprite->Draw(backBuffer, IsCameraControlled, IsCameraTrack);
	if (m_pBackgroundLayerFrontSprite != 0)
		m_pBackgroundLayerFrontSprite->Draw(backBuffer, IsCameraControlled, IsCameraTrack);
}

void
ControllerBackground::SetBackgroundMain(BackBuffer& backBuffer, const char* pcFileName)
{
	m_pBackgroundMainSprite = new Background();
	m_pBackgroundMainSprite->Initialise(backBuffer.CreateSprite(pcFileName));
}

void
ControllerBackground::SetBackgroundLayerBack(BackBuffer& backBuffer, const char* pcFileName)
{
	m_pBackgroundLayerBackSprite = new Background();
	m_pBackgroundLayerBackSprite->Initialise(backBuffer.CreateSprite(pcFileName));
}

void
ControllerBackground::SetBackgroundLayerFront(BackBuffer& backBuffer, const char* pcFileName)
{
	m_pBackgroundLayerFrontSprite = new Background();
	m_pBackgroundLayerFrontSprite->Initialise(backBuffer.CreateSprite(pcFileName));
}

void
ControllerBackground::MonitorVelocity(Background& background,Player& player, bool Horizontal, bool Vertical)
{
	if (Horizontal)
	{
		if (player.GetHorizontalVelocity() != 0)
		{
			if (player.GetHorizontalVelocity() > 0)
				background.SetHorizontalVelocity(-Layer2VelocityX);
			else if (player.GetHorizontalVelocity() < 0)
				background.SetHorizontalVelocity(Layer2VelocityX);
		}
		else
		{
			background.SetHorizontalVelocity(0);
		}
	}
	if (Vertical)
	{
		if (player.GetVerticalVelocity() != 0)
		{
			if (player.GetVerticalVelocity() > 0)
				background.SetVerticalVelocity(-Layer2VelocityY);
			else if (player.GetVerticalVelocity() < 0)
				background.SetVerticalVelocity(Layer2VelocityY);
		}
		else
		{
			background.SetVerticalVelocity(0);
		}
	}


	if (background.GetPositionX() > background.GetWidth())
	{
		background.SetPositionX(0);
	}
	if (background.GetPositionY() > background.GetHeight())
	{
		background.SetPositionY(0);
	}
}