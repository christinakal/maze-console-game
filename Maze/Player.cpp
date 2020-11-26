#include "Player.h"
#include "Key.h"
#include <iostream>

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	:PlaceableActor(0, 0)
	,m_pCurrentKey(nullptr)
	,m_money(0)
	,m_lives(kStartingNumberOfLives)
{

};

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(int color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = false;
}

void Player::UseKey()
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
	
}

void Player::Draw()
{
	cout << "@";
}
