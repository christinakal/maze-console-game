#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	:PlaceableActor(x, y)
	, m_CurrentMovementX(0)
	, m_CurrentMovementY(0)
	, m_DirectionX(0)
	, m_DirectionY(0)
	, m_MovementInX(deltaX)
	, m_MovementInΥ(deltaY)
{
	if (m_MovementInX != 0)
	{
		m_DirectionX = 1;
	}
	if (m_MovementInΥ != 0)
	{
		m_DirectionY = 1;
	}
	
}

void Enemy::Draw()
{
	cout << (char)153;
}

void Enemy::Update()
{
	if (m_MovementInX != 0)
	{
		UpdateDirection(m_CurrentMovementX, m_DirectionX, m_MovementInX);
	}
	if (m_MovementInΥ != 0)
	{
		UpdateDirection(m_CurrentMovementY, m_DirectionY, m_MovementInΥ);
	}

	this->SetPosition(m_pPosition->x + m_DirectionX, m_pPosition->y + m_DirectionY);
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	current += direction;
	if (abs(current) > movement)
	{
		current = movement * direction;
		direction *= -1;
	}
}