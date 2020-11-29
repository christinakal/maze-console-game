#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Game.h"

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"



using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow =77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;


Game::Game()
	:m_GameOver(false)
	,m_UserQuit(false)
{

}

Game::~Game()
{

}

bool Game::Load()
{
	return m_Level.Load("SecondLevel.txt", m_Player.GetXPositionPointer(), m_Player.GetYPositionPointer());
}

void Game::Run()
{
	Draw();
	m_GameOver = Update();

	// if game over re draw it in it's initial state
	if (m_GameOver)
	{
		Draw();
	}
}


bool Game::GameOver()
{
	return m_GameOver;
}

bool Game::Update()
{
	char input = _getch();
	int arrowInput = 0;
	int newPlayerX = m_Player.GetXPosition();
	int newPlayerY = m_Player.GetYPosition();

	// Handle User Key Input
	if (input == kArrowInput)
	{
		arrowInput = _getch();
	}

	if ((input == kArrowInput && arrowInput == kLeftArrow) || (char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}

	else if ((input == kArrowInput && arrowInput == kRightArrow) || (char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}
	else if ((input == kArrowInput && arrowInput == kUpArrow) || (char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}
	else if ((input == kArrowInput && arrowInput == kDownArrow) || (char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}
	else if (input == kEscapeKey)
	{
		m_UserQuit = true;
	}

	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_Player.DropKey();
	}

	// In case position never changed
	if (newPlayerX == m_Player.GetXPosition() && newPlayerY == m_Player.GetYPosition())
	{
		return false;
	}
	else
	{
		return HandleCollision(newPlayerX, newPlayerY);
	}

}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{
	PlaceableActor* collidedActor = m_Level.UpdateActors(newPlayerX, newPlayerY);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
		if (collidedEnemy)
		{
			collidedEnemy->Remove();
			m_Player.SetPosition(newPlayerX, newPlayerY);

			m_Player.DecrementLives();
			if (m_Player.GetLives() < 0)
			{
				return true;
			}
		}

		Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
		if (collidedMoney)
		{
			collidedMoney->Remove();
			m_Player.AddMoney(collidedMoney->GetWorth());
			m_Player.SetPosition(newPlayerX, newPlayerY);
		}

		Key* collidedKey = dynamic_cast<Key*>(collidedActor);
		if (collidedKey)
		{
			if (!m_Player.HasKey())
			{
				m_Player.PickupKey(collidedKey);
				collidedKey->Remove();
				m_Player.SetPosition(newPlayerX, newPlayerY);
				//PlayerKeyPickupSound();
			}
		}

		Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
		if (collidedDoor)
		{
			if (!collidedDoor->IsOpen())
			{
				if (m_Player.HasKey(collidedDoor->GetColor()))
				{
					collidedDoor->IsOpen();
					collidedDoor->Remove();
					m_Player.UseKey();
					m_Player.SetPosition(newPlayerX, newPlayerY);
					//PlayerDoorOpenSound();
				}
				else
				{
					//PlayerDoorClosedSound();
				}
			}
			else
			{
				m_Player.SetPosition(newPlayerX, newPlayerY);
			}
		}

		Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
		if (collidedGoal)
		{
			collidedGoal->Remove();
			m_Player.SetPosition(newPlayerX, newPlayerY);
			return true;
		}
	}
	else if (m_Level.IsSpace(newPlayerX, newPlayerY)) // no collision
	{
		m_Player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_Level.IsWall(newPlayerX, newPlayerY)) 
	{
		// wall collision - do nothing
	}

	return false;
}


void Game::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_Level.Draw();

	// Set cursor position for Player
	COORD currentCursorPosition;

	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_Level.GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

}