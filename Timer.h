#ifndef _TIMER_H
#define _TIMER_H
#endif // !_TIMER_H

#include <sdl2/SDL.h>

// Used for counting frames of our game
class Timer {
private:
	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

public:
	static Timer* Instance();
	static void Release();

	void Reset();
	// returns delta time
	float DeltaTime();
	// setting time scale
	void TimeScale(float t);
	// returns time scale
	float TimeScale();

	// update our timer
	void Update();

private:
	// constructor
	Timer();
	// destructor
	~Timer();

};