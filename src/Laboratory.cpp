#include "Laboratory.hpp"

// Initializes a new lab from a specific file
Laboratory::Laboratory(std::string& file)
{
	loadFromFile(file);
	m_map_name = file;
}

// New lab with specified dimensions
Laboratory::Laboratory(int width, int height)
{
	m_map = std::vector<std::vector<Tile>>(height, std::vector<Tile>(width));
	m_width = width;
	m_height = height;
	m_map_name = "UNKNOWN";
}

// New lab with size (0, 0)
Laboratory::Laboratory() : Laboratory(0, 0) {}

// Tile at coordinates
auto Laboratory::tile_at(int x, int y) -> Tile&
{
	return m_map.at(y).at(x);
}

// Tile at the point
auto Laboratory::tile_at(Point position) -> Tile&
{
	return tile_at(position.x, position.y);
}

// Width of the map
auto Laboratory::width() -> int
{
	return m_width;
}

// Height of the map
auto Laboratory::height() -> int
{
	return m_height;
}

// Returns wether the coordinates is in range of the map
auto Laboratory::in_range(int x, int y) -> bool
{
	bool x_in_range = x > -1 && x < width();
	bool y_in_range = y > -1 && y < height();

	return x_in_range && y_in_range;
}

// Returns wether the point is in range of the map
auto Laboratory::in_range(Point position) -> bool
{
	return in_range(position.x, position.y);
}

// Returns wether the specified tile is not air and in range of the map
auto Laboratory::is_walkable(int x, int y) -> bool
{
	if (in_range(x, y))
	{
		return (tile_at(x, y).type() != "stone");
	}
	return false;
}

// Returns wether the specified tile is not air and in range of the map
auto Laboratory::is_walkable(Point position) -> bool
{
	return is_walkable(position.x, position.y);
}

// Prints the lab to the console and marks the bot
auto Laboratory::print(Point bot_position, int bot_direction) -> void
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	#ifdef _WIN32
	std::system("cls"); // clear command for win32
	#else
	std::system("clear"); // clear command for posix compatible systems
	#endif

	std::cout << "Termbot - " << m_map_name << std::endl; // draw header
	for (auto i = 0; i < 60; i++)
	{
		std::cout << "=";
	}
	std::cout << std::endl;

	for (unsigned int y = 0; y < m_map.size(); y++)
	{
		auto row = m_map.at(y);
		for (unsigned int x = 0; x < row.size(); x++)
		{
			auto tile = row.at(x);

			if (bot_position.x == x && bot_position.y == y)
			{
				switch (bot_direction)
				{
				case 0:
					std::cout << '>';
					break;
				case 1:
					std::cout << 'v';
					break;
				case 2:
					std::cout << '<';
					break;
				case 3:
					std::cout << '^';
					break;
				}
			}
			else if (tile.type() == "air")
			{
				std::cout << ' ';
			}
			else if (tile.type() == "stone")
			{
				std::cout << '#';
			}
			else if (tile.type() == "mark")
			{
				std::cout << 'x';
			}
		}
		std::cout << std::endl;
	}
}

// Loads the lab from file (resets map data, width and height)
auto Laboratory::loadFromFile(std::string& file) -> void
{
	std::ifstream lab_file;
	lab_file.open(file);

	if (!lab_file.is_open())
	{
		throw std::exception();
	}

	std::string current_line;
	m_map = std::vector<std::vector<Tile>>();

	while (std::getline(lab_file, current_line))
	{
		std::vector<Tile> row;
		for (unsigned int i = 0; i < current_line.length(); i++)
		{
			Tile tile;
			switch (current_line.at(i))
			{
			case '#':
				tile = Tile("stone");
				break;
			case 'x':
				tile = Tile("mark");
				break;
			default:
				tile = Tile("air");
			}
			row.push_back(tile);
		}
		m_map.push_back(row);
	}
	if (m_map.size() > 0)
	{
		m_width = m_map.at(0).size();
	}
	m_height = m_map.size();
}