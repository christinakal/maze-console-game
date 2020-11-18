#pragma once
#include <string>

class Level
{
	char* m_pLevelData;
	int m_Height;
	int m_Width;

public:
	Level();

	~Level();

	bool Load(std::string LevelName, int* PlayerX, int* PlayerY);
	void Draw(int x, int y);
	bool IsSpace(int x, int y);
	bool IsDoor(int x, int y); 
	bool IsKey(int x, int y);
	bool IsGoal(int x, int y);

	void PickUpKey(int x, int y);
	void OpenDoor(int x, int y);

	int GetHeight() { return m_Height; }
	int GetWidth() { return m_Width;  }

private:
	bool Convert(int* PlayerX, int* PlayerY);
	int GetIndexFromCoordinates(int x, int y);
};