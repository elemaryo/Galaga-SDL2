#include "StartScreen.h"


StartScreen::StartScreen(){

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top Bar Entities
	// put it in the center
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200,0,0 });
	mHiScore = new Texture("HI-SCORE", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerOneScore = new Scoreboard();
	mTopScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();

	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);

	// since bound to parent, they share a y value (at 0) so move it on x by 35%
	// if top bar moves, all of them translate with it
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
	mPlayerTwo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	mHiScore->Pos(VEC2_ZERO);

	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.33f, 40.0f));
	mPlayerTwoScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.36f, 40.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.05f, 40.0f));

	mTopScore->Score(30000);

	// assign top bar as child of start screen
	mTopBar->Parent(this);

	// Logo Entities
	mLogo = new Texture("galagalogo.png", 0, 0, 360, 180);
	mLogo->Parent(this);
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));
	mAnimatedLogo = new AnimatedTexture("galagalogo.png", 0, 0, 360, 180, 3, 1.0f, AnimatedTexture::vertical);
	mAnimatedLogo->Parent(this);
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));

	//PlayMode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.68f));
	mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230,230,230 });
	mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230,230,230 });

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);

	mOnePlayerMode->Pos(Vector2(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));

	mPlayModes->Parent(this);

	// Cursor Entites
	mCursor = new Texture("Cursor.png");
	mCursor->Parent(mPlayModes);
	mCursor->Pos(Vector2(-175.0f, -35.0f));
	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;


	//Screen Animation Variables
	ResetAnimation();


	mStars = BackgroundStars::Instance();
	mStars->Scroll(true);
}

StartScreen::~StartScreen() {
	//Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne = NULL;
	delete mPlayerTwo;
	mPlayerTwo = NULL;
	delete mHiScore;
	mHiScore = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;
	delete mTopScore;
	mTopScore = NULL;
	delete mPlayerTwoScore;
	mPlayerTwoScore = NULL;

	//Freeing Logo Entities
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;

	//Freeing Cursor
	delete mCursor;
	mCursor = NULL;

	//Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;
	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);

}

int StartScreen::SelectedMode() {

	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}

	else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
}

// change start screen position based on animation start and end for timer duration
void StartScreen::Update(){
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Interp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));
		
		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
			mStars->Scroll(false);
		}

		// cancel animation if key is pressed
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN)|| mInput->KeyPressed(SDL_SCANCODE_UP)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}

	else {
		mAnimatedLogo->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}

		else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render() {
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();

	mPlayerOneScore->Render();
	mPlayerTwoScore->Render();
	mTopScore->Render();

	if (!mAnimationDone) {
		mLogo->Render();
	}

	else {
		mAnimatedLogo->Render();
	};

	mCursor->Render();
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
};