#include "ScreenManager.h"

ScreenManager *ScreenManager::sInstance = NULL;

ScreenManager *ScreenManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{
	// Initialize Background Stars
	mBackgroundStars = BackgroundStars::Instance();

	//Initialize StartScreen
	mStartScreen = new StartScreen();

	mPlayScreen = new PlayScreen();

	mInput = InputManager::Instance();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{

	mInput = NULL;

	BackgroundStars::Release();
	mBackgroundStars = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update()
{
	mBackgroundStars->Update();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();
		//update current screen if enter is pressed
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = play;
			//after switch the animation replays
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();
		}
		break;

	case play:
		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
		}
		break;
	}
};

void ScreenManager::Render()
{

	mBackgroundStars->Render();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;

	case play:
		mPlayScreen->Render();
		break;
	}
}
