#pragma once
#include "PlacableActor.h"

class Key : public PlaceableActor
{
public:
	Key(int x, int y, int color)
		:PlaceableActor(x, y, color)
	{

	}

	virtual void Draw() override;
};
