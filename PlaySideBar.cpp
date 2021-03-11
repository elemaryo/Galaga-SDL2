#include "PlaySideBar.h"


PlaySideBar::PlaySideBar(){
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("black.png");
	mBackground->Parent();
	mBackground->Pos(VEC2_ZERO);
}

PlaySideBar::~PlaySideBar(){
	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;
}

void PlaySideBar::Update(){}

void PlaySideBar::Render(){
	mBackground->Render();
}