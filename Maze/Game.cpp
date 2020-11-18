#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Game.h"

using namespace std;

constexpr int kOpenDoorColor = 10;
constexpr int kCloseDoorColor = 12;
constexpr int kRegularColor = 7;

Game::Game()
	:m_GameOver(false)
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
	char input = (char)_getch();

	int newPlayerX = m_Player.GetXPosition();
	int newPlayerY = m_Player.GetYPosition();

	switch (input)
	{
	case 'W':
	case 'w':
		newPlayerY--;
		break;
	case 'A':
	case 'a':
		newPlayerX--;
		break;
	case 's':
	case 'S':
		newPlayerY++;
		break;
	case 'D':
	case 'd':
		newPlayerX++;
		break;
	default:
		break;

	}

	if (m_Level.IsSpace(newPlayerX, newPlayerY))
	{
		m_Player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_Level.IsKey(newPlayerX, newPlayerY))
	{
		m_Level.PickUpKey(newPlayerX, newPlayerY);
		m_Player.PickupKey();
		m_Player.SetPosition(newPlayerX, newPlayerY);
		//PlayPickupKeySound();
	}
	else if (m_Level.IsDoor(newPlayerX, newPlayerY) && m_Player.HasKey())
	{
		m_Level.OpenDoor(newPlayerX, newPlayerY);
		m_Player.UseKey();
		m_Player.SetPosition(newPlayerX, newPlayerY);
		//PlayDoorOpenedSound();
	}
	else if (m_Level.IsDoor(newPlayerX, newPlayerY) && !m_Player.HasKey())
	{
		//PlayDoorClosedSound();
	}
	else if (m_Level.IsGoal(newPlayerX, newPlayerY))
	{
		m_Player.SetPosition(newPlayerX, newPlayerY);
		return true;
	}
	return false;
}

void Game::Draw()
{

	system("cls");
	for (int y = 0; y < m_Level.GetHeight(); y++) {
		for (int x = 0; x < m_Level.GetWidth(); x++) {
			if (m_Player.GetXPosition() == x && m_Player.GetYPosition() == y)
			{
				m_Player.Draw();
			}
			else
			{
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (m_Level.IsDoor(x, y))
				{
					if (m_Player.HasKey())
					{
						SetConsoleTextAttribute(console, kOpenDoorColor);
					}
					else
					{
						SetConsoleTextAttribute(console, kCloseDoorColor);
					}
				}
				else
				{
					SetConsoleTextAttribute(console, kRegularColor);
				}
				m_Player.Draw();
			}
		}
		cout << endl;
	}
}