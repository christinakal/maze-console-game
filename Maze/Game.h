#pragma once
#include "Player.h"
#include "Level.h"

class Game
{
	Player m_Player;
	Level m_Level;

	bool m_GameOver;

public:
	Game();
	~Game();

	bool Load();
	void Run();

	bool GameOver();

private:
	bool Update();
	void Draw();
};