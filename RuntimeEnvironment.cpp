#include "RuntimeEnvironment.hpp"

RuntimeEnvironment::RuntimeEnvironment(Bot& robot, bool debug)
{
	m_bot = robot;
	m_debug = debug;
}

auto RuntimeEnvironment::struct_end_index(int current) -> int
{
	int level = 0;
	for (int i = current + 1; i < m_bot.program().size(); i++)
	{
		if (m_bot.program().at(i) == "end" )
		{
			if (level == 0)
			{
				return i;
			}
			else
			{
				level--;
			}
		}
		else if (m_bot.program().at(i) == "while" || m_bot.program().at(i) == "if")
		{
			level++;
		}
	}
	throw_error("Missing end token", current);
	return -1;
}

auto RuntimeEnvironment::function_call(std::string function_name, int& token_index) -> bool
{
	int function_index = token_index;
	auto call_search = m_function_maps.find(function_name);
	if (call_search != m_function_maps.end())
	{
		std::vector<std::string> args(m_args_count[function_name]);
		for (int c = 0; c < m_args_count[function_name]; c++)
		{
			args.at(c) = m_bot.program().at(++token_index);
		}
		return m_function_maps[function_name](args, m_bot);
	}
	throw_error("Function not found " + function_name, function_index);
	return false;
}

auto RuntimeEnvironment::throw_error(std::string msg, int token_index) -> void
{
	m_err_stack.push("LINE " + std::to_string(m_bot.program_indices().at(token_index))
					 + " : " + std::to_string(token_index) + " Warning / Error"  + "\n\t" + msg);
}

auto RuntimeEnvironment::execute() -> void
{
	std::string err_msgs;
	std::stack<std::pair<std::string, int>> structure_stack;
	for (int i = 0; i < m_bot.program().size(); i++)
	{
		std::string current_token = m_bot.program().at(i);

		if (m_debug)
		{
			std::cout << structure_stack.size() << " -> " << current_token << std::endl;
		}

		if (current_token == "while" || current_token == "if")
		{
			int structure_index = i;
			bool condition_mod = false;

			std::string next_token = m_bot.program().at(++i);
			std::string condition_call;

			if (next_token == "not")
			{
				condition_mod = true;
				condition_call = m_bot.program().at(++i);
			}
			else
			{
				condition_call = next_token;
			}

			bool condition_value = function_call(condition_call, i);
			if (condition_mod)
			{
				condition_value = !condition_value;
			}

			if (!condition_value)
			{
				i = struct_end_index(i);
			}
			else
			{
				structure_stack.push(std::pair<std::string, int>(current_token, structure_index));
			}
		}
		else if (current_token == "else")
		{
			// Do something here
		}
		else if (current_token == "end")
		{
			if (structure_stack.empty())
			{
				throw_error("Unused end token", i);
			}
			else
			{
				auto structure_ident = structure_stack.top();
				if (structure_ident.first == "while")
				{
					i = structure_ident.second - 1;
				}
				else if (structure_ident.first == "if")
				{
					// Do some cleanup here
				}
				else
				{
					throw_error("Unknown structure ident " + structure_ident.first, structure_ident.second);
				}
				structure_stack.pop();
			}
		}
		else
		{
			function_call(current_token, i);
		}

		m_bot.laboratory().print(m_bot.position(), m_bot.direction());
		while (!m_err_stack.empty())
		{
			err_msgs += m_err_stack.top() + "\n";
			m_err_stack.pop();
		}
		std::cout << err_msgs << std::flush;
	}
}

auto RuntimeEnvironment::bind(std::string name, int args_count, std::function<bool(std::vector<std::string>, Bot&)> fnc) -> void
{
	m_function_maps[name] = fnc;
	m_args_count[name] = args_count;
}
