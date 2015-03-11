#ifndef TERMBOT_RTENV_H_
#define TERMBOT_RTENV_H_

#include "Bot.hpp"
#include <functional>
#include <vector>
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

class RuntimeEnvironment
{
private:
	std::stack<std::string> m_err_stack;
	Bot	m_bot;
	bool m_debug;
	std::map<std::string, std::function<bool(std::vector<std::string>, Bot&)>>	m_function_maps;
	std::map<std::string, int> m_args_count;
	auto struct_end_index(int current) -> int;
	auto function_call(std::string function_name, int& token_index) -> bool;
	auto throw_error(std::string msg, int token_index) -> void;
public:
	RuntimeEnvironment(Bot& robot, bool debug);
	auto execute()																								-> void;
	auto bind(std::string name, int args_count, std::function<bool(std::vector<std::string>, Bot&)> fnc)	-> void;
};

#endif