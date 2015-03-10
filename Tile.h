#ifndef TERMBOT_TILE_H_
#define TERMBOT_TILE_H_

#include <string>

// Stores the type of a tile
class Tile
{
private:
	// Internal type of the tile
	std::string		m_type;
public:
	// New tile with specified type
	Tile(std::string type);
	// New tile with type "air"
	Tile();
	// Type of the tile
	auto type()						-> std::string&;
};

#endif