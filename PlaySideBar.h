#ifndef _PLAYSIDEBAR_H

#define _PLAYSIDEBAR_H

#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity
{
private:
	Timer *mTimer;
	AudioManager *mAudio;

	Texture *mBackground;

	Texture *mHighLabel;
	Texture *mScoreLabel;
	Scoreboard *mHighScoreBoard;

	Texture *mPlayerOneLabel;
	float mBlinkTimer;
	float mBlnkInterval;
	bool mPlayOneVisible;

	Scoreboard *mPlayerOneScore;

	// player health
	static const int MAX_SHIP_TEXTURES = 5;
	GameEntity *mShips;
	Texture *mShipTextures[MAX_SHIP_TEXTURES];
	//integer to keep track of total ships the player has
	int mTotalShips;
	Scoreboard *mTotalShipsLabel;

	GameEntity *mFlags;
	std::vector<Texture *> mFlagTextures;
	int mRemaingingLevels;
	int mFlagXOffset;
	// delay for each flag
	float mFlagTimer;
	float mFlagInterval;

private:
	void ClearFlags();
	// to determine which flag to add next
	void AddNextFlag();
	void AddFlag(std::string filename, float width, int value);

public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetShips(int ships);
	void SetLevel(int level);

	void Update();
	void Render();
};

#endif // !_PLAYSIDEBAR_H