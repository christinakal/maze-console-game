#include <iostream>
#include <conio.h>

using namespace std;

constexpr char kPlayer = '@';

// --- define functions
int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
bool UpdatePlayerPosition( char level[], int& playerX, int& playerY, int width, bool& playerHasKey);


int main()
{
	constexpr int kWidth = 25;
	constexpr int kHeight = 15;

	char LevelArray[]{	'+','-', '-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','*','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' ,'|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','-','-','-','-','-','-','-','-','-','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
						'|',' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ','X','|',
						'+','-', '-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+' };

	int playerX = 1;
	int playerY = 1;
	bool playerHasKey = false;
	bool GameOver = false;

	while (!GameOver)
	{
		// --- clear the screen before draw level
		system("cls");
		DrawLevel(LevelArray, kWidth, kHeight, playerX, playerY);
		GameOver = UpdatePlayerPosition(LevelArray, playerX, playerY, kWidth, playerHasKey);
	}
	system("cls");
	DrawLevel(LevelArray, kWidth, kHeight, playerX, playerY);
	cout << "CONGRATULATIONS! YOU WON!";
	

}


// --- create functions
int GetIndexFromCoordinates(int x, int y, int width)
{
	return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY)
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
	else if (level[index] == '*')
	{
		playerHasKey = true;
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'D' && playerHasKey == true)
	{
		level[index] = ' ';
		playerHasKey = false;
		playerX = newPlayerX;
		playerY = newPlayerY;
	}
	else if (level[index] == 'X')
	{
		level[index] = ' ';
		playerX = newPlayerX;
		playerY = newPlayerY;
		return true;
	}
	return false;
}