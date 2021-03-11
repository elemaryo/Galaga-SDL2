#include "Star.h"

bool Star::sScroll = false;

void Star::Scroll(bool b) {

	sScroll = b;
}

Star::Star(int layer) : Texture("stars.png",0,0,4,4) {
	
	mTimer = Timer::Instance();

	// picks a number between 0-3
	int starColor = rand() % 4;

	// each one of the star is 4 x 4 so this allows it to skip a color
	mClipRect.x = starColor * 4;

	// returns a random value between 0 - screenwidth/height
	Pos(Vector2(rand() % Graphics::Instance()->SCREEN_WIDTH, rand() % Graphics::Instance()->SCREEN_HEIGHT));
	
	mFlickerTimer = 0.0f;

	// returns a value with 0.15 at minimum and the max value at 0.45 + 0.15 = 0.60
	mFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f;

	float invLayer = 1.0f / layer;	
	// scale star size by layer
	Scale(VEC2_ONE * invLayer);

	mScrollSpeed = 4.0f / layer;

}

Star::~Star(){

	mTimer = NULL;
}

// star scrolls down to the end then repositioned to a random positon
void Star::ScrollStar(){
	
	Translate(VEC2_UP * mScrollSpeed);

	Vector2 pos = Pos(local);

	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = rand() % Graphics::Instance()->SCREEN_WIDTH;
		Pos(pos);
	}

}

void Star::Update() {

	mFlickerTimer += mTimer->DeltaTime();
	
	if (mFlickerTimer >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTimer = 0.0f;
	}

	if (sScroll) {
		ScrollStar();
	}
}

void Star::Render() {

	if (mVisible) {
		Texture::Render();
	}
}