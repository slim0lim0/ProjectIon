// This Include:
#ifndef __SPRITE_H__
#define __SPRITE_H__

class BackBuffer;
class Texture;

class Sprite
{
	//Member Methods

public:
	Sprite();
	~Sprite();

	bool Initialise(Texture& texture);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void Draw(BackBuffer& backBuffer, bool IsCameraControlled, bool IsCameraTrack);

	void SetX(int X);
	void SetY(int Y);

	int GetX() const;
	int GetY() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetCenter(int x, int y);
	void SetHandleCenter();

	int GetWidth() const;
	int GetHeight() const;

	Texture* GetTexture();

	void* GetPixels();
	int GetPitch();

	bool LockTexture();
	bool UnlockTexture();

protected:

private:
	//Sprite(const Sprite& sprite);
	//Sprite& operator=(const Sprite& sprite);

	// Member Data

public:

protected:
	Texture* m_pTexture;
	int m_x;
	int m_y;

	float m_angle;
	int m_centerX;
	int m_centerY;
	
	int m_width;
	int m_height;

private:

};

#endif // __SPRITE_H__