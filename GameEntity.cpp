#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
}

GameEntity::~GameEntity()
{
	mParent = NULL;
}

void GameEntity::Pos(Vector2 pos)
{
	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	// if the space is local or no parent in world
	if (space == local || mParent == NULL)
	{
		return mPos;
	}
	// return position of parent in world
	// rotate position of child to match the parent as they affect each other
	return mParent->Pos(world) + RotateVector(mPos, mParent->Rotation(local));
}
// setter for our rotation
void GameEntity::Rotation(float r)
{
	mRotation = r;
	// keep our rotation between 360
	if (mRotation > 360.0f)
	{
		mRotation -= 360.0f;
	}

	if (mRotation < 0.0f)
	{
		mRotation += 360.0f;
	}
}

// getter for rotation
float GameEntity::Rotation(SPACE space)
{
	if (space == local || mParent == NULL)
	{
		return mRotation;
	}
	// return world rotation for parent + our current rotation
	return mParent->Rotation(world) + mRotation;
}

// setter for active
void GameEntity::Active(bool active)
{
	mActive = active;
}

// getter for active
bool GameEntity::Active()
{
	return mActive;
}

// setter for parent
void GameEntity::Parent(GameEntity *parent)
{
	// bring the childs local position to be relative to parent object
	// get world position of object
	mPos = Pos(world) - parent->Pos(world);
	mParent = parent;
}

// getter for parent

GameEntity *GameEntity::Parent()
{
	return mParent;
}

void GameEntity::Update()
{
}

void GameEntity::Render()
{
}