#include "GameManager.h"

GameManager *GameManager::sInstance = NULL;

GameManager *GameManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
	}

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

// constructor
GameManager::GameManager()
{
	mQuit = false;

	// initialize graphics
	mGraphics = Graphics::Instance();
	mTimer = Timer::Instance();

	// if graphics initialization fails
	if (!Graphics::Initalized())
	{
		mQuit = true;
	}

	mParent = new GameEntity(100.0f, 400.0f);
	mChild = new GameEntity(100.0f, 500.0f);
	//testing child position
	// printf("Child local pos (%f,%f)\n", mChild->Pos(GameEntity::world).x, mChild->Pos(GameEntity::world).y);
	mChild->Parent(mParent);
	// printf("Child local pos (%f,%f)\n", mChild->Pos(GameEntity::world).x, mChild->Pos(GameEntity::world).y);
}

GameManager::~GameManager()
{
	Graphics::Release();
	mGraphics = NULL;
	Timer::Release();
	mTimer = NULL;

	delete mParent;
	delete mChild;
}

// game loop
void GameManager::Run()
{
	while (!mQuit)
	{
		// while SDL is receiving events
		//update time in the beginning of the loop
		mTimer->Update();
		while (SDL_PollEvent(&mEvents) != 0)
		{

			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		// if our time is bigger than a fraction of our frame rate then do a render
		// ensures 60fps meaning we want 0.017 seconds for each frame
		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			// Render calls into graphics
			mGraphics->Render();
			// reset after timer
			mTimer->Reset();
		}
	}
}