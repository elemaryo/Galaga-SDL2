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

	//player created in start new game function
	mPlayer = NULL;
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

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	// delete the old level
	delete mLevel;
	// create new level
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);
}

// set base variables for a new game
void PlayScreen::StartNewGame()
{
	// delete old player
	delete mPlayer;
	// set new player
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	// set active to false so the player does not move till the level starts
	mPlayer->Active(false);

	mStars->Scroll(false);
	mSideBar->SetHighScore(30000);
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
	mAudio->PlayMusic("gamestart.wav", 0);

	
}

bool PlayScreen::GameOver() {

	if (!mLevelStarted) {
		return false;
	}

	return (mLevel->State() == Level::gameover);
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
	if (mGameStarted)
	{
		// keeps 1UP lable blinking
		if (mCurrentStage > 0) {
			mSideBar->Update();
		}
		
		// update level once it started

		if (mLevelStarted) {
			mLevel->Update();

			// check if level state is finished or not and tell playscreen
			if (mLevel->State() == Level::finished) {
				mLevelStarted = false;
			}
		}

		mPlayer->Update();
		
	}
}

void PlayScreen::Render()
{

	mSideBar->Render();

	if (!mGameStarted)
	{
		mStartLabel->Render();
	}

	if (mGameStarted)
	{
		if (mLevelStarted) {
			mLevel->Render();
		}

		mPlayer->Render();
	}
}