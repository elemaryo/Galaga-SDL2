#include "PlayScreen.h"

PlayScreen::PlayScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mStars = BackgroundStars::Instance();
	
	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
}

PlayScreen::~PlayScreen() {

	mTimer = NULL;
	mInput = NULL;
	mStars = NULL;

	delete mSideBar;
	mSideBar = NULL;
}

void PlayScreen::Update(){
	
	mSideBar->Update();
}

void PlayScreen::Render() {
	
	mSideBar->Render();
}