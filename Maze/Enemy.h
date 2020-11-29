#pragma once
#include "PlacableActor.h"

class Enemy : public PlaceableActor
{
public:
	Enemy(int x, int y, int deltaX = 0, int deltaY = 0);

	virtual void Draw() override;
	virtual void Update() override;

private:
	int m_MovementInX;
	int m_MovementInΥ;

	// how much the enemy moved in x and y
	int m_CurrentMovementX;
	int m_CurrentMovementY;

	int m_DirectionX;
	int m_DirectionY;

	void UpdateDirection(int& current, int& direction, int& movement);
};