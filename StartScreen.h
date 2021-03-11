#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H


#include "AnimatedTexture.h"
#include "InputManager.h"
#include "BackgroundStars.h" 
#include "Scoreboard.h"

using namespace QuickSDL;

// inherit from game entity to attach objects to start screen
class StartScreen : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;

	// Top Bar Entities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mTopScore;
	Scoreboard* mPlayerTwoScore;

	// Logo Entities
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	// Cursor Entities
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	// player one or two
	int mSelectedMode;

	//Play Mode Entites
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;

	//Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	// how long for animation
	float mAnimationTotalTime;
	// timer for animation
	float mAnimationTimer;
	bool mAnimationDone;

	BackgroundStars* mStars;

public:
	StartScreen();
	~StartScreen();

	int SelectedMode();

	void Update();
	void Render();

	void ChangeSelectedMode(int change);

	void ResetAnimation();
};

#endif // !_STARTSCREEN_H