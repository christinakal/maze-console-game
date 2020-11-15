#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

// --- constants
constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;

// --- functions declarations
void GetLevelDimentions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int CursorX, int CursorY);
int GetIndexFromXY(int x, int y, int width);

void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();

bool EditLevel(char* pLevel, int& CursorX, int& CursorY, int width, int height);
void SaveLevel(char* pLevel, int width, int height);

int main()
{
    int LevelWidth;
    int LevelHeight;

    GetLevelDimentions(LevelWidth, LevelHeight);

    char* pLevel = new char[LevelWidth * LevelHeight];

    for (int i = 0; i < LevelWidth * LevelHeight; i++)
    {
        pLevel[i] = ' ';
    }
    int CursorX = 0;
    int CursorΥ = 0;
    bool DoneEditing = false;

    while (!DoneEditing)
    {
        system("cls");
        DisplayLevel(pLevel, LevelWidth, LevelHeight, CursorX, CursorΥ);
        DoneEditing = EditLevel(pLevel, CursorX, CursorΥ, LevelWidth, LevelHeight);
    }

    system("cls");
    DisplayLevel(pLevel, LevelWidth, LevelHeight, -1, -1);

    SaveLevel(pLevel, LevelWidth, LevelHeight);


    delete[] pLevel;
    pLevel = nullptr;
}


void GetLevelDimentions(int& width, int& height)
{
    cout << "Please enter the width of the level:" << endl;
    cin >> width;

    cout << "Please enter the height of the level:" << endl;
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int CursorX, int CursorY)
{

    DisplayTopBorder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBorder();
        for (int x = 0; x < width; x++)
        {
            if(CursorX == x && CursorY == y)
            {
                cout << kCursor;
            }
            else
            {
                int index = GetIndexFromXY(x, y, width);
                cout << pLevel[index];
            }

        }
        DisplayRightBorder();
    }

    DisplayBottomBorder(width);
}

void DisplayTopBorder(int width)
{
    cout << kTopLeftBorder;

    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(int width)
{
    cout << kBottomLeftBorder;

    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;

}

void DisplayLeftBorder()
{
    cout << kVerticalBorder << endl;
}

void DisplayRightBorder()
{
    cout << kVerticalBorder << endl;
}

int GetIndexFromXY(int x, int y, int width)
{
    return x + (y * width);
}

bool EditLevel(char* pLevel, int& CursorX, int& CursorY, int width, int height)
{
    int NewCursorX = CursorX;
    int NewCursorY = CursorY;

    int IntInput = _getch();

    if (IntInput == kArrowInput)
    {
        int ArrowInput = _getch();

        switch (ArrowInput)
        {
            case kLeftArrow:
                NewCursorX--;
                break;
            case kRightArrow:
                NewCursorX++;
                break;
            case kUpArrow:
                NewCursorY--;
                break;
            case kDownArrow:
                NewCursorY++;
                break;
        }

        // --- check mouse positions
        if (NewCursorX < 0)
        {
            NewCursorX = 0;
        }
        else if (NewCursorX == width)
        {
            NewCursorX = width - 1;
        }

        if (NewCursorY < 0)
        {
            NewCursorY = 0;
        }
        else if (NewCursorY == width)
        {
            NewCursorY = width - 1;
        }

        CursorX = NewCursorX;
        CursorY = NewCursorY;
    }
    else
    {
        if (IntInput == kEscape)
        {
            return true;
        }
        else
        {
            int index = GetIndexFromXY(NewCursorX, NewCursorY, width);
            pLevel[index] = (char)IntInput;
        }
    }

    return false;
}

void SaveLevel(char* pLevel, int width, int height)
{
    cout << "Pick a name for your level (eg: Level1.txt): ";
    string LevelName;
    cin >> LevelName;

    LevelName.insert(0, "../");

    ofstream LevelFile;
    LevelFile.open(LevelName);
    if (!LevelFile)
    {
        cout << "Opening file failed!" << endl;
    }
    else
    {
        LevelFile << width << endl;
        LevelFile << height << endl;
        LevelFile.write(pLevel, width * height);

        if (!LevelFile)
        {
            cout << "Write failed.." << endl;
        }
        LevelFile.close();
    }
}