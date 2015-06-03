#include "Bot.hpp"

// Creates a new bot at the point, with the specified facing direction and the working laboratory
Bot::Bot(Point position, int direction, Laboratory& lab)
{
	m_position = position;
	m_direction = direction;
	m_lab = lab;
}

/*
// Creates a new bot at the specified position in a laboratory that does fit
Bot::Bot(Point position)
{
	Bot(position, 0, Laboratory(position.x + 1, position.y + 1));
}
*/
// Creates a new bot in an empty laboratory
Bot::Bot()
{
	
}

// Working laboratory of the bot
auto Bot::laboratory() -> Laboratory
{
	return m_lab;
}

// Current position of the bot
auto Bot::position() -> Point
{
	return m_position;
}

// Current facing direction of the bot
auto Bot::direction() -> int
{
	return m_direction;
}

auto Bot::program() -> std::vector<std::string>&
{
	return m_program;
}

auto Bot::program_indices() -> std::vector<int>&
{
	return m_program_indices;
}

// Tries to move the bot forwards
auto Bot::move() -> bool
{
	Point old_position = m_position;
	switch (m_direction)
	{
	case 0: // right
		if (m_lab.is_walkable(m_position.right()))
		{
			m_position.move_right();
		}
		break;
	case 1: // down
		if (m_lab.is_walkable(m_position.down()))
		{
			m_position.move_down();
		}
		break;
	case 2: // left
		if (m_lab.is_walkable(m_position.left()))
		{
			m_position.move_left();
		}
		break;
	case 3: // up
		if (m_lab.is_walkable(m_position.up()))
		{
			m_position.move_up();
		}
		break;
	}
	return !(m_position == old_position);
}

// Rotates the bot leftwards
auto Bot::rotate_left() -> void
{
	if (--m_direction < 0)
	{
		m_direction = 3;
	}
}

// Rotates the bot rightwards
auto Bot::rotate_right() -> void
{
	if (++m_direction > 3)
	{
		m_direction = 0;
	}
}

// Sets a mark on the ground
auto Bot::set_mark() -> void
{
	m_lab.tile_at(m_position) = Tile("mark");
}

// Checks wether there is a stone in the front
auto Bot::stone_front() -> bool
{
	Point fw = m_position.forward(m_direction);
	if (m_lab.in_range(fw))
	{
		if (m_lab.tile_at(fw).type() == "stone")
		{
			return true;
		}
	}
	return false;
}

// Checks wether there is a stone on the left side
auto Bot::stone_left() -> bool
{
	rotate_left();
	bool stone = stone_front();
	rotate_right();

	return stone;
}

// Checks wether there is a stone on the right side
auto Bot::stone_right() -> bool
{
	rotate_right();
	bool stone = stone_front();
	rotate_left();
	
	return stone;
}

// Checks wether the bot sits on a mark
auto Bot::on_mark() -> bool
{
	return m_lab.tile_at(m_position).type() == "mark";
}

bool is_tab_or_whitespace(char c)
{
	return c == '\t' || c == ' ' || c == '\n';
}

auto Bot::load_from_file(std::string file) -> void
{
	std::ifstream botFile;
	botFile.open(file);

	if (!botFile.is_open())
	{
		std::cout << "Failed to read bot file" << std::endl;
		throw - 3;
	}
	m_program = std::vector<std::string>();
	m_program_indices = std::vector<int>();

	std::string current_token;
	int line_index = 1;
	while (getline(botFile, current_token))
	{
		std::string current_str;
		for (auto c : current_token)
		{
			if (is_tab_or_whitespace(c))
			{
				current_str.erase(std::remove_if(current_str.begin(), current_str.end(), is_tab_or_whitespace), current_str.end());
				if (current_str.length() > 0)
				{
					m_program.push_back(current_str);
					m_program_indices.push_back(line_index);
				}
				current_str = std::string();
			}
			else
			{
				current_str += c;
			}
		}
		current_str.erase(std::remove_if(current_str.begin(), current_str.end(), is_tab_or_whitespace), current_str.end());
		if (current_str.length() > 0)
		{
			m_program.push_back(current_str);
			m_program_indices.push_back(line_index);
		}
		line_index++;
	}
}
