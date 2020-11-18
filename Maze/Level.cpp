#include <iostream>
#include <fstream>
#include "Level.h"


using namespace std;

constexpr char WALL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOOR = (char)'|';
constexpr char GOAL = (char)36;

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

		m_pLevelData = new char[m_Width * m_Height];
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

void Level::Draw(int x, int y)
{
	int index = GetIndexFromCoordinates(x, y);
	cout << m_pLevelData[index];
}

bool Level::IsSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsDoor(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == DOOR;
}

bool Level::IsKey(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == KEY;
}

bool Level::IsGoal(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == GOAL;
}

void Level::PickUpKey(int x, int y)
{
	 m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

void Level::OpenDoor(int x, int y)
{

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
			case '*':
				m_pLevelData[index] = KEY;
				break;
			case 'D':
				m_pLevelData[index] = DOOR;
				break;
			case 'X':
				m_pLevelData[index] = GOAL;
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (PlayerX != nullptr && PlayerY != nullptr) {
					*PlayerX = x;
					*PlayerY = y;
				}
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
