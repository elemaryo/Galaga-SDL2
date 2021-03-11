#ifndef _PLAYSIDEBAR_H

#define _PLAYSIDEBAR_H

#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;

public:
	PlaySideBar();
	~PlaySideBar();

	void Update();
	void Render();
};

#endif // !_PLAYSIDEBAR_H