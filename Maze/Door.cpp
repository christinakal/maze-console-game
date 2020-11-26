#include <iostream>
#include <Windows.h>
#include "Door.h"

using namespace std;

Door::Door(int x, int y, int color, int closedColor)
	:PlaceableActor(x, y, color)
	,m_IsOpen(false)
	,m_ClosedColor(closedColor)
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_IsOpen)
	{
		SetConsoleTextAttribute(console, m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, m_ClosedColor);
	}
	cout << "|";

	SetConsoleTextAttribute(console, kRegularColor);
}