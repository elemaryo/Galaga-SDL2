#ifndef _LEVEL_H
#define _LEVEL_H

#include "InputManager.h"
// to control the playside bar and background star
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"

class Level : public GameEntity
{

public:
    // keeps track of the level states
    // finished if all enemies are destroyed
    enum LEVEL_STATES {running, finished, gameover};

private:
    Timer* mTimer;
    PlaySideBar* mSideBar;

    BackgroundStars* mStars;

    // current stage
    int mStage;
    // true after stage and flags are shown
    bool mStageStarted;

    float mLabelTimer;

    Texture* mStageLabel;
    Scoreboard* mStageNumber;
    float mStageLabelOnScreen;
    float mStageLabelOffScreen;

    Texture* mReadyLabel;
    float mReadyLabelOnScreen;
    float mReadyLabelOffScreen;

    Player* mPlayer;
    // check if player is hit
    bool mPlayerHit;
    // respawn delay after animation
    float mPlayerRespawnDelay;
    float mPlayerRespawnTimer;
    float mPlayerRespawnLabelOnScreen;

    Texture* mGameOverLabel;
    // let the playscreen know the game is over
    bool mGameOver;
    float mGameOverDelay;
    float mGameOverTimer;
    float mGameOverLabelOnScreen;

    LEVEL_STATES mCurrentState;

private:
    void StartStage();
    // handle all labels
    void HandleStartLabels();
    void HandleCollisions();
    void HandlePlayerDeath();

public:
    Level(int stage, PlaySideBar* sideBar, Player* player);
    ~Level();

    LEVEL_STATES State();

    void Update();
    void Render();
};

#endif