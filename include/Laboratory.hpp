#ifndef TERMBOT_LABORATORY_H_
#define TERMBOT_LABORATORY_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

#include "Point.hpp"
#include "Tile.hpp"

// Laboratory, containing map and meta data
class Laboratory
{
private:
	// Internal map storage
	std::vector<std::vector<Tile>>	m_map;
	// File name of the map
	std::string						m_map_name;
	// Internal map width
	int								m_width;
	// Internal map height
	int								m_height;
public:
	// Initializes a new lab from a specific file
	Laboratory(std::string& file);
	// New lab with specified dimensions
	Laboratory(int width, int height);
	// New lab with size (0, 0)
	Laboratory();

	// Tile at coordinates
	auto tile_at(int x, int y)							-> Tile&;
	// Tile at the point
	auto tile_at(Point position)						-> Tile&;
	// Returns wether the specified tile is not air and in range of the map
	auto is_walkable(int x, int y)						-> bool;
	// Returns wether the specified tile is not air and in range of the map
	auto is_walkable(Point position)					-> bool;
	// Returns wether the coordinates is in range of the map
	auto in_range(int x, int y)							-> bool;
	// Returns wether the point is in range of the map
	auto in_range(Point position)						-> bool;
	// Width of the map
	auto width()										-> int;
	// Height of the map
	auto height()										-> int;
	// Prints the lab to the console and marks the bot
	auto print(Point bot_position, int bot_direction)	-> void;
	// Loads the lab from file (resets map data, width and height)
	auto loadFromFile(std::string& file)				-> void;
};

#endif