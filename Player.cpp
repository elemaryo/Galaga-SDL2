#include "Player.h"

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	// player is invisible till stage starts
	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;

	mShip = new Texture("playership.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 300.0f;
	// move between 0 and 800
	mMoveBounds = Vector2(40.0f, 720.0f);

	mDeathAnimation = new AnimatedTexture("playerexp.png", 0, 0, 125, 128, 4, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	// make it play once and not loop
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i] = new Bullet();
	}
};

Player::~Player() {
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mShip;
	mShip = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;
	}
}

void Player::HandleMovement(){
	
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		// translate vector to the right
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
	}

	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		// translate vector to the left
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
	}

	// check bounds
	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}

	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Pos(pos);
}

void Player::HandleFiring() {
	// if space is pressed
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		// check for inactive bullets
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Pos());
				mAudio->PlaySFX("fire.wav");
				break;
			}
		}
	}
}

void Player::Visible(bool visible) {

	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Lives() {
	return mLives;
}

int Player::Score(){
	return mScore;
}

void Player::AddScore(int change) {
	mScore += change;
}

void Player::WasHit() {

	mLives--;
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("playerdestroyed.wav");
}

void Player::Update(){
	// handle player movement only if it is not animating
	if (mAnimating){
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->isAnimating();
	}

	else {
		// similar to visible in render
		if (Active()) {
			HandleMovement();
			// player can fire while moving
			HandleFiring();
		}
	}

	// update bullet
	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Update();
	}
}

void Player::Render(){
	// check if it is visible
	if (mVisible) {
		// draw animated texture
		if (mAnimating) {

			mDeathAnimation->Render();
		}
		// otherwise draw player ship
		else {

			mShip->Render();
		}
	}

	// render bullet
	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Render();
	}

}