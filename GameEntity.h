#ifndef _GAMEENTITY_H
#define _GAMEENTITY_H
#endif // !_GAMEENTITY_H

#include "MathHelper.h"


// base class for all our game entity objects we create

class GameEntity {
public:
	// this will tell us if the object is in the local space or world space
	// local space is relative to parent, world space is relative to the grid
	enum SPACE {local = 0, world = 1};

private:
	Vector2 mPos;
	float mRotation;
	// tells you if the object is active
	bool mActive;

	// get one game entity and make it a child of another game entity
	GameEntity* mParent;

public:
	// constructor
	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	// setter for object mPosition
	void Pos(Vector2 pos);

	//getter for object mPosition
	Vector2 Pos(SPACE space = world);

	// setter for object mRotation
	void Rotation(float rotation);

	// getter for object rotation
	float Rotation(SPACE space = world);

	// setter for object active state
	void Active(bool active);

	// getter for object active state
	bool Active();

	// function to set parent of the object - either null or object
	void Parent(GameEntity* parent);

	// getter for parent object
	GameEntity* Parent();

	virtual void Update();
	virtual void Render();
};