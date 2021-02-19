#include "Timer.h"

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance() {
	if (sInstance == NULL) {
		sInstance = new Timer();
	}

	return sInstance;
}

void Timer::Release() {
	delete sInstance;
	sInstance = NULL;
}

Timer::Timer() {
	Reset();
	// set time scale
	mTimeScale = 1.0f;
}

Timer::~Timer() {

}

void Timer::Reset() {
	// return number of ms since library was initialized
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

// getter for delta time
float Timer::DeltaTime() {
	return mDeltaTime;
}

// setter for time scale
void Timer::TimeScale(float t) {
	mTimeScale = t;
}

// getter for time scale
float Timer::TimeScale() {
	return mTimeScale;
}

void Timer::Update() {
	// ticks between last reset and our current time
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	// convert mElapsed to float
	mDeltaTime = mElapsedTicks * 0.001f;
}