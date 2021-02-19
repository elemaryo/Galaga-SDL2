#include "GameEntity.h"

GameEntity::GameEntity(float x, float y) {
	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
}

GameEntity::~GameEntity() {
	mParent = NULL;
}

void GameEntity::Pos(Vector2 pos) {
	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space) {
	// if the space is local or no parent in world
	if (space == local || mParent == NULL) {
		return mPos;
	}
	// return position of parent in world
	// rotate position of child to match the parent as they affect each other
	return mParent->Pos(world) + RotateVector(mPos, mParent->Rotation(local));
}