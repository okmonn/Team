#include "Map.h"

Map::Map()
{
	//Ground::Getsize();
	ground = std::make_unique<Ground>(Vec2f{ 640.0f * 8,340.0f  });
}
Map::~Map()
{
}
