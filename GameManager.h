#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#endif // !_GAMEMANAGER_H

#include "Graphics.h"
#include "Timer.h"

class GameManager {

private:
	// game manager instance
	static GameManager* sInstance;
	
	const int FRAME_RATE = 60;

	bool mQuit;

	// graphics pointer
	Graphics* mGraphics;

	// timer pointer
	Timer* mTimer;

	// catch user events such as button presses
	SDL_Event mEvents;

// public functions
public:
	static GameManager* Instance();
	static void Release();

	void Run();

// private functions
private:
	// constructor
	GameManager();
	// destructor
	~GameManager();
};
