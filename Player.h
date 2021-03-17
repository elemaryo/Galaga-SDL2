#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"

using namespace QuickSDL;

class Player : public GameEntity {

private:
	// initializing managers
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	// true if player is visible on the screen
	bool mVisible;
	bool mAnimating;
	// player score
	int mScore;
	// player lives
	int mLives;

	Texture* mShip;

	AnimatedTexture* mDeathAnimation;

	float mMoveSpeed;
	// minimum and maxmium x that the player can translate between
	Vector2 mMoveBounds;

	// maximum of 2 bullets in galaga
	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

private:
	// will take care of all movement handling
	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Visible(bool visible);
	// find out if player is animating or not
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	// called when a collision between enemy and bullet
	void WasHit();

	void Update();
	void Render();
};

#endif // !_PLAYER_H
