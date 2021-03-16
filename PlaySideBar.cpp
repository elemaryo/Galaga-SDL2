#include "PlaySideBar.h"

PlaySideBar::PlaySideBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("black.png");
	mBackground->Parent(this);
	mBackground->Pos(Vector2(45.0f, 300.0f));
	mBackground->Scale(3.0f, 10.0f);

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, {150, 0, 0});
	mHighLabel->Parent(this);
	mHighLabel->Pos(Vector2(-25.0f, 0.0f));

	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, {150, 0, 0});
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(Vector2(25.0f, 32.0f));

	mHighScoreBoard = new Scoreboard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Pos(Vector2(90.0f, 64.0f));

	mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 32, {150, 0, 0});
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(Vector2(-45.0f, 160.0f));

	mBlinkTimer = 0.0f;
	mBlnkInterval = 0.5f;
	mPlayOneVisible = true;

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(90.0f, 192.0f));

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Pos(Vector2(-40.0f, 420.0f));

	for (int i = 0; i < MAX_SHIP_TEXTURES; i++)
	{
		mShipTextures[i] = new Texture("playership.png");
		mShipTextures[i]->Parent(mShips);
		// i % 3 is incremented until it gets to 3 then resets to 0 and starts all over again
		// i/3 makes sure once it reaches 3, it would start a new row
		mShipTextures[i]->Pos(Vector2(62.0f * (i % 3), 70.0f * (i/3));
	}

	mTotalShipsLabel = new Scoreboard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Pos(Vector2(140.0f, 80.0f));

	// Render flags
	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Pos(Vector2(-50.0f, 65.0f));

	mFlagTimer = 0.0f;
	mFlagInterval = 0.2f;
}

PlaySideBar::~PlaySideBar()
{
	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighLabel;
	mHighLabel = NULL;

	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreBoard;
	mHighScoreBoard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < MAX_SHIP_TEXTURES; i++)
	{
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}

	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;

	delete mFlags;
	mFlags = NULL;
	ClearFlags();
}

void PlaySideBar::ClearFlags()
{
	for (int i = 0; o < mFlagTextures.size(); i++)
	{
		delete mFlagTextures[i];
		mFlagTextures = NULL;
	}

	mFlagTextures.clear();
}

void PlaySideBar::SetHighScore(int score)
{
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlaySideBar::SetShips(int ships)
{
	mTotalShips = ships;

	// this is to prevent a refresh of textures if the textures are less than max ships
	if (mTotalShips > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Score(ships);
	}
}

void PlaySideBar::SetLevel(int level)
{
	// clear flags as this is a new level
	ClearFlags();

	mRemaingingLevels = level;
	// reset offset
	mFlagXOffset = 0.0f;
}

void PlaySideBar::AddNextFlag()
{

	if (mRemaingingLevels >= 50)
	{
		AddFlag("fiftylevelflag.png", 62.0f, 50);
	}

	else if (mRemaingingLevels >= 30)
	{
		AddFlag("thirtylevelflag.png", 62.0f, 30);
	}

	else if (mRemaingingLevels >= 20)
	{
		AddFlag("twentylevelflag.png", 62.0f, 20);
	}

	else if (mRemaingingLevels >= 10)
	{
		AddFlag("tenlevelflag.png", 54.0f, 10);
	}

	else if (mRemaingingLevels >= 5)
	{
		AddFlag("fivelevelflag.png", 30.0f, 5);
	}

	else
	{
		AddFlag("onelevelflag.png", 30.0f, 1);
	}
}

void PlaySideBar::AddFlag(std::string filename, float width, int value)
{

	// we need to know which index we are focusing on
	// before the pushback
	int index = mFlagTextures.size();

	// the flag offset is the current half width and previous
	// flag half width
	if (index > 0)
	{
		mFlagXOffset += width * 0.5f;
	}

	mRemaingingLevels - value;

	mFlagTextures.push_back(new Texture(filename));
	mFlagTextures[index]->Parent(mFlags);
	// you add more flag textures to the right
	mFlagTextures[index]->Pos(VEC2_RIGHT * mFlagXOffset);
	// prepare offset for next flag to be set
	mFlagXOffset += width * 0.5f;

	// play sound everytime a flag is added
	mAudio->PlaySFX("flagsound.wav");
}

void PlaySideBar::Update()
{
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlnkInterval)
	{
		mPlayOneVisible = !mPlayOneVisible;
		mBlinkTimer = 0.0f;
	}

	if (mRemaingingLevels > 0)
	{
		mFlagTimer = mTimer->DeltaTime();
		if (mFlagTimer >= mFlagInterval)
		{
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlaySideBar::Render()
{
	mBackground->Render();
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();

	if (mPlayOneVisible)
	{
		mPlayerOneLabel->Render();
	}

	mPlayerOneScore->Render();

	// render lives based on max ship textures and total ships available
	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; i++)
	{
		mShipTextures[i]->Render();
	}

	// render additional lives only after max textures
	if (mTotalShips > MAX_SHIP_TEXTURES)
	{
		mTotalShipsLabel->Render();
	}

	// render flags
	for (int i = 0; i < mFlagTextures.size(); i++)
	{
		mFlagTextures[i]->Render();
	}
}