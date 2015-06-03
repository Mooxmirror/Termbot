#include "Tile.hpp"

// New tile with specified type
Tile::Tile(std::string type)
{
	m_type = type;
}

// New tile with type "air"
Tile::Tile() : Tile::Tile("air") {}

// Type of the tile
auto Tile::type() -> std::string&
{
	return m_type;
}