#pragma once
#include "PlacableActor.h"

class Goal : public PlaceableActor
{
public:
	Goal(int x, int y);

	virtual void Draw() override;
};