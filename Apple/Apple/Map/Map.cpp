#include "Map.h"

Map::Map()
{
	//Ground::Getsize();
	ground = std::make_unique<Ground>(120.0f, 640.0f * 8);

}
Map::~Map()
{
}