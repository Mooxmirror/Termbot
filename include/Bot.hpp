#ifndef TERMBOT_BOT_H_
#define TERMBOT_BOT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>

#include "Laboratory.hpp"

// Bot can do control and movement operations
class Bot
{
private:
	// Laboratory the bot is acting on
	Laboratory					m_lab;
	// Current position of the bot in the lab
	Point						m_position;
	// Facing direction of the bot
	int							m_direction;
	// Program tokens
	std::vector<std::string>	m_program;
	// Program line indices
	std::vector<int>			m_program_indices;
public:
	// Creates a new bot at the point, with the specified facing direction and the working laboratory
	Bot(Point position, int direction, Laboratory& lab);
	// Creates a new bot at the specified position in a laboratory that does fit
	//Bot(Point position);
	// Creates a new bot in an empty laboratory
	Bot();

	// Working laboratory of the bot
	auto laboratory()						-> Laboratory;
	// Current position of the bot
	auto position()							-> Point;
	// Current facing direction of the bot
	auto direction()						-> int;
	// Program tokens
	auto program()							-> std::vector<std::string>&;
	// Program token line indices
	auto program_indices()					-> std::vector<int>&;
	// Tries to move the bot forwards
	auto move()								-> bool;
	// Rotates the bot leftwards
	auto rotate_left()						-> void;
	// Rotates the bot rightwards
	auto rotate_right()						-> void;
	// Sets a mark on the ground
	auto set_mark()							-> void;
	// Checks wether there is a stone in the front
	auto stone_front()						-> bool;
	// Checks wether there is a stone on the left side
	auto stone_left()						-> bool;
	// Checks wether there is a stone on the right side
	auto stone_right()						-> bool;
	// Checks wether the bot sits on a mark
	auto on_mark()							-> bool;

	auto load_from_file(std::string file)	-> void;
};

#endif