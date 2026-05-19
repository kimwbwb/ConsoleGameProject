#pragma once

#include "Actor/Actor.h"

class Box : public Craft::Actor
{
	// RTTIµî·Ï
	TYPE_DECLARATIONS(Box, Actor)

public:
	Box(const Craft::Vector2& position);
};

