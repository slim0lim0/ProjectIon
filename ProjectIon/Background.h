#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "entity.h"
#include "BackBuffer.h"


class Background : public Entity
{
public:
	Background();
	~Background();

	void Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTrack);
private:

};



#endif // __PLAYERSHIP_H_