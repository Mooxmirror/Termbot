// Termbot (Terminal robot)
// (c) 2015 Lennart Espe (github@mooxmirror.io)

/*
Termbot commands:
move - moves the bot in the facing direction
rotate (left / right) - rotates the bot in the target direction

Structures:
while [condition]
if [condition]

Use 'end' to end a structure

Conditions:
stone [front / left / right] - if a stone is in the front, left or right
mark on - if the robot is in front of a mark
mark set - sets a mark at the current position

Negate condition using 'not'
*/

#include <iostream>
#include <string>
#include <vector>

#include "RuntimeEnvironment.h"

int main()
{
	std::cout << "Terminal bot" << std::endl << "(c) 2015 mooxmirror" << std::endl;

	std::cout << "Bot script path: ";
	std::string bot_path; std::getline(std::cin, bot_path);

	std::cout << "Laboratory path: ";
	std::string lab_path; std::getline(std::cin, lab_path);

	Laboratory my_lab(lab_path);
	Bot my_bot(Point(4, 0), 0, my_lab);

	my_bot.load_from_file(bot_path);

	RuntimeEnvironment rt_env(my_bot, false);

	// Bind all commands
	
	rt_env.bind("stone", 1, [](std::vector<std::string> args, Bot& robot) {
		if (args[0] == "left")
		{
			return robot.stone_left();
		}
		else if (args[0] == "right")
		{
			return robot.stone_right();
		}
		else if (args[0] == "front")
		{
			return robot.stone_front();
		}
		std::cerr << "Unknown argument: " << args.at(1) << std::endl;
		return false;
	});
	rt_env.bind("mark", 1, [](std::vector<std::string> args, Bot& robot) {
		if (args[0] == "on")
		{
			return robot.on_mark();
		}
		else if (args[0] == "set")
		{
			robot.set_mark();
			return true;
		}
		std::cerr << "Unknown argument: " << args.at(1) << std::endl;
		return false;
	});
	rt_env.bind("move", 0, [](std::vector<std::string> args, Bot& robot) {
		return robot.move();
	});
	rt_env.bind("rotate", 1, [](std::vector<std::string> args, Bot& robot) {
		if (args[0] == "left")
		{
			robot.rotate_left();
			return true;
		}
		else if (args[0] == "right")
		{
			robot.rotate_right();
			return true;
		}
		std::cerr << "Unknown argument: " << args.at(1) << std::endl;
		return false;
	});

	rt_env.execute();

	return 0;
}