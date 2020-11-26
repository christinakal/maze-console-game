#pragma once
#include "PlacableActor.h"

class Door : public PlaceableActor
{
public:
	Door(int x, int y, int color, int closedColor);
	virtual void Draw() override;

	bool IsOpen() { return m_IsOpen; }
	void Open() { m_IsOpen = true; }

private:
	bool m_IsOpen;
	int m_ClosedColor;
};