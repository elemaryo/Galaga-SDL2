#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
// to control the playside bar and background star
#include "PlaySideBar.h"
#include "BackgroundStars.h"

class Level : public GameEntity
{
private:
    Timer *mTimer;
    PlaySideBar *mSideBar;

    BackgroundStars *mStars;

    // current stage
    int mStage;
    // true after stage and flags are shown
    bool mStageStarted;

    float mLabelTimer;

    Texture *mStageLabel;
    Scoreboard *mStageNumber;
    float mStageLabelOnScreen;
    float mStageLabelOffScreen;

    Texture *mReadyLabel;
    float mReadyLabelOnScreen;
    float mReadyLabelOffScreen;

private:
    void StartStage();

public:
    Level(int stage, PlaySideBar *sideBar);
    ~Level();
    void Update();
    void Render();
}

#endif