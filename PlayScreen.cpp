#include "PlayScreen.h"

PlayScreen::PlayScreen()
{

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mStars = BackgroundStars::Instance();
	mAudio = AudioManager::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.85f, Graphics::Instance()->SCREEN_HEIGHT * 0.05f));

	mStartLabel = new Texture("START", "emulogic.ttf", 32, {150, 0, 0});
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
}

PlayScreen::~PlayScreen()
{

	mAudio = NULL;
	mTimer = NULL;
	mInput = NULL;
	mStars = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	// delete the old level
	delete mLevel
		// create new level
		mLevel = new Level(mCurrentStage, mSideBar);
}

// set base variables for a new game
void PlayScreen::StartNewGame()
{
	mStars->Scroll(false);
	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(2);
	mGameStarted = false;
	mAudio->PlayMusic("gamestart.wav", 0);
	mCurrentStage = 0;
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		// wait for a second then start level
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}
	}

	else
	{
		// if the music is done which means level started
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}

	// if the game and level start then start the flashing
	if (mGameStarted && mLevelStarted)
	{
		mSideBar->Update();
		// update level once it started
		mLevel->Update();
	}
}

void PlayScreen::Render()
{

	mSideBar->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
	}

	if (mGameStarted && mLevelStarted)
	{
		mLevel->Render();
	}
}