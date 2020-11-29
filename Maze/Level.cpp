#include <windows.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"


using namespace std;

constexpr char WALL = (char)219;

Level::Level()
	:m_pLevelData(nullptr)
	,m_Height(0)
	,m_Width(0)
{

}

Level::~Level()
{
	if (m_pLevelData != nullptr)
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}
}

bool Level::Load(std::string LevelName, int* PlayerX, int* PlayerY)
{
	LevelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(LevelName);
	if (!levelFile)
	{
		cout << "Opening file failed!" << endl;
		return false;
	}
	else
	{
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		m_Width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		m_Height = atoi(temp);

		m_pLevelData = new char[(long long)m_Width * m_Height];
		levelFile.read(m_pLevelData, (long long)m_Width * (long long)m_Height);
		

		// --- handle warnings
		bool anyWarnings = Convert(PlayerX, PlayerY);
		if (anyWarnings)
		{
			cout << "There were some warnings in the level data, see above." << endl;
			system("pause");
		}
		return true;

	}
}

void Level::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, kRegularColor);

	// Draw the level
	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			int IndexToPrint = GetIndexFromCoordinates(x, y);
			cout << m_pLevelData[IndexToPrint];
		}
		cout << endl;
	}

	COORD actorCursorPosition;

	//Draw actors
	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		if ((*actor)->IsActive())
		{
			actorCursorPosition.X = (*actor)->GetXPosition();
			actorCursorPosition.Y = (*actor)->GetYPosition();
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}
}

bool Level::IsSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsWall(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == WALL;
}

bool Level::Convert(int* PlayerX, int* PlayerY)
{
	bool anyWarnings = false;

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);

			switch (m_pLevelData[index])
			{
			case '+':
			case '-':
			case '|':
				m_pLevelData[index] = WALL;
				break;
			case 'r':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, kRedColor));
				break;
			case 'g':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, kGreenColor));
				break;
			case 'b':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, kBlueColor));
				break;
			case 'R':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, kRedColor, kRedColorSolid));
				break;
			case 'G':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, kGreenColor, kGreenColorSolid));
				break;
			case 'B':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, kBlueColor, kBlueColorSolid));
				break;
			case 'X':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Goal(x, y));
				break;
			case '$':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (PlayerX != nullptr && PlayerY != nullptr) {
					*PlayerX = x;
					*PlayerY = y;
				}
				break;
			case 'e':
				m_pActors.push_back(new Enemy(x, y));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'h':
				m_pActors.push_back(new Enemy(x, y, 3,0));
				m_pLevelData[index] = ' '; // clear the level
				break;
			case 'v':
				m_pLevelData[index] = ' '; // clear the level
				m_pActors.push_back(new Enemy(x, y, 0, 2));
				m_pLevelData[index] = ' ';
				break;
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}

	return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
	return x + y * m_Width;
}


PlaceableActor* Level::UpdateActors(int x, int y)
{
	PlaceableActor* collidedActor = nullptr;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		(*actor)->Update(); // Update all actors

		if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition())
		{

			// should only be able to collide with one actor
			assert(collidedActor == nullptr);
			collidedActor = (*actor);

		}
	}

	return collidedActor;
}