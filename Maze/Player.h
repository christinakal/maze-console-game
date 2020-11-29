#pragma once
#include "Point.h"
#include "PlacableActor.h"
#include "Key.h"

class Player : public PlaceableActor
{
public:
	Player();	

	bool HasKey();
	bool HasKey(int color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();

	void AddMoney(int money) { m_money += money; }
	void GetMoney() { m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual void Draw() override;

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
};