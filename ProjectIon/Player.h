#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "BackBuffer.h"


class Player : public Entity
{
public:
	Player();
	~Player();

	void Process(float deltaTime, int levelWidth, int levelHeight);
	void Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTrack);
private:

};



#endif // __PLAYERSHIP_H_