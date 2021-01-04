#pragma once
#include "stdafx.h"
enum class RunMode
{
	Seek,
	Evade
};

struct InventorySlots
{
	eItemType type;
	int amount;
};

struct PointsOfInterestIsSkippable
{
	Elite::Vector2 location;
	bool canSkip;
};