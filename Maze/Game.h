#pragma once
#include "Player.h"
#include "Level.h"

class Game
{
	Player m_Player;
	Level m_Level;

	bool m_GameOver;
	bool m_UserQuit;

public:
	Game();
	~Game();

	bool Load();
	void Run();

	bool GameOver();
	bool DidUserQuit() { return m_UserQuit; }
	int GetPlayerLives() { return m_Player.GetLives();  }

private:
	bool Update();
	void Draw();

	bool HandleCollision(int newPlayerX, int newPlayerY);
};