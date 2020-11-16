#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

constexpr char kPlayer = '@';
constexpr char WALL = 219;
constexpr char KEY = 232;
constexpr char DOOR = '|';
constexpr char GOAL = 36;

constexpr int kOpenDoorColor = 10;
constexpr int kCloseDoorColor = 12;
constexpr int kRegularColor = 7;


// --- define functions
int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey);
bool UpdatePlayerPosition( char level[], int& playerX, int& playerY, int width, bool& playerHasKey);
void PlayDoorClosedSound();
void PlayDoorOpenedSound();
void PlayPickupKeySound();
void PlayWinSound();
char* LoadLevel(string LevelName, int& Width, int& Height);
bool ConvertLevel(char* Level, int Width, int Height, int& playerY, int& playerΧ);

int main()
{
	int Width = 25;
	int Height = 25;

	char* LevelArray = LoadLevel("SecondLevel.txt", Width, Height);

	int playerX = 1;
	int playerY = 1;

	// --- handle warnings
	bool anyWarnings = ConvertLevel(LevelArray, Width, Height, playerX, playerY);
	if (anyWarnings)
	{
		cout << "There were some warnings in the level data, see above." << endl;
		system("pause");
	}

	bool playerHasKey = false;
	bool GameOver = false;

	while (!GameOver)
	{
		// --- clear the screen before draw level
		system("cls");
		DrawLevel(LevelArray, Width, Height, playerX, playerY, playerHasKey);
		GameOver = UpdatePlayerPosition(LevelArray, playerX, playerY, Width, playerHasKey);
	}
	system("cls");
	DrawLevel(LevelArray, Width, Height, playerX, playerY, playerHasKey);
	cout << "CONGRATULATIONS! YOU WON!";
	PlayWinSound();
	
	delete[] LevelArray;
}


// --- create functions

char* LoadLevel(string LevelName, int& Width, int& Height)
{
	LevelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(LevelName);
	if (!levelFile)
	{
		cout << "Opening file failed!" << endl;
		return nullptr;
	}
	else
	{
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		Width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		Height = atoi(temp);

		char* levelData = new char[Width * Height];
		levelFile.read(levelData, Width * Height);
		return levelData;
	}
}

bool ConvertLevel(char* Level, int Width, int Height, int& playerΧ, int& playerY)
{
	bool anyWarnings = false;

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			int index = GetIndexFromCoordinates(x, y, Width);

			switch (Level[index])
			{
			case '+':
			case '-':
			case '|':
				Level[index] = WALL;
				break;
			case '*':
				Level[index] = KEY;
				break;
			case 'D':
				Level[index] = DOOR;
				break;
			case 'X':
				Level[index] = GOAL;
				break;
			case '@':
				Level[index] = ' ';
				playerΧ = x;
				playerY = y;
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << Level[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}

	return anyWarnings;
}

int GetIndexFromCoordinates(int x, int y, int width)
{
	return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (playerX == x && playerY == y)
			{
				cout << kPlayer;
			}
			else
			{
				int index = GetIndexFromCoordinates(x, y, width);

				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				if (level[index] == DOOR)
				{
					if (playerHasKey)
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
				cout << level[index];
			}
					}
		cout << endl;
	}
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey)
{
	char input = _getch();

	int newPlayerX = playerX;
	int newPlayerY = playerY;

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

	int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);

	if (level[index] == ' ')
	{
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == KEY)
	{
		playerHasKey = true;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		PlayPickupKeySound();
	}
	else if (level[index] == DOOR && playerHasKey == true)
	{
		level[index] = ' ';
		playerHasKey = false;
		playerX = newPlayerX;
		playerY = newPlayerY;
		PlayDoorOpenedSound();
	}
	else if (level[index] == DOOR && !playerHasKey)
	{
		PlayDoorClosedSound();
	}
	else if (level[index] == GOAL)
	{
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		return true;
	}
	return false;
}

void PlayDoorClosedSound()
{
	Beep(500, 75);
	Beep(500, 75);
}

void PlayDoorOpenedSound()
{
	Beep(1397, 200);
}

void PlayPickupKeySound()
{
	Beep(1568, 200);
}

void PlayWinSound()
{
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1568, 200);
	Beep(1245, 1000);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1397, 200);
	Beep(1175, 1000);
}