#pragma once
#include <string>
#include <vector>

class PlaceableActor;

class Level
{
	char* m_pLevelData;
	int m_Height;
	int m_Width;

	std::vector<PlaceableActor*> m_pActors;

public:
	Level();

	~Level();

	bool Load(std::string LevelName, int* PlayerX, int* PlayerY);
	void Draw();


	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);
	PlaceableActor* UpdateActors(int x, int y);

	int GetHeight() { return m_Height; }
	int GetWidth() { return m_Width;  }

private:
	bool Convert(int* PlayerX, int* PlayerY);
	int GetIndexFromCoordinates(int x, int y);
};