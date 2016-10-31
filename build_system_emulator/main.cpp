#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "task.h"
#include <sstream>
#include <map>
#include <set>
#include <memory>
#include <stdexcept>
#include <exception>
#include "my_exception.h"

std::vector<std::shared_ptr<task>> tasks;
std::map<std::string, std::shared_ptr<task>> maps;

std::string trim(const std::string& str, const std::string& whitespace = " \t\n") {
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return "";

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

void exec(const char* cmd) {
	
	int status = std::system(cmd);
	if (status != 0) {
		throw std::runtime_error("Wrong action \"" + std::string(cmd) + "\"");
	}

}


bool dfs(std::string command) {

	std::shared_ptr<task> ptr = maps[command];

	ptr->set_status(0);

	//check for dependences
	for (auto d : ptr->get_dependeces()) {
		if (maps.count(d) == 0) {
			throw my_exception("Uncorrect dependence: no target \"" + command + "\"");
		}
		if (maps[d]->get_status() == -1) {
			dfs(d);
		} else if (maps[d]->get_status() == 0){
			throw my_exception("Wrong dependences: cycle");
		}
	}

	std::cout << command << std::endl;
	
	//execute actions
	for (std::string action : ptr->get_actions()) {
		exec(action.c_str());
	}

	ptr->set_status(1);

	return true;
	
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "No arguments" << std::endl;
		return 1;
	}

	std::string command = argv[1];

	std::ifstream fin("Makefile");
	if (!fin.is_open()) {
		std::cout << "File can't be open. Check if it is \"Makefile\"" << std::endl;
		return 1;
	}

	std::string str;
	while (std::getline(fin, str)) {
		int m = str.find(":");
		if (m >= 0) {
			if (!tasks.empty() && tasks[tasks.size() - 1]->get_actions().empty()) {
				std::cout << "Warning: no actions for target "<< tasks[tasks.size() - 1]->get_target() << std::endl;
			}
			std::string name = trim(str.substr(0, m));
			if (name.empty()) {
				std::cout << "Uncorrect target" << std::endl;
				return 1;
			}
			task t(name);
			std::shared_ptr<task> ptr = std::make_shared<task>(t);
			tasks.push_back(ptr);
			maps.insert(std::make_pair(name, ptr));
			std::vector<std::string> dependeces;
			std::istringstream iss(str.substr(m + 1, str.length()));
			for (std::string s; iss >> s; )
				dependeces.push_back(s);
			tasks[tasks.size() - 1]->set_dependences(dependeces);
		} else {
			//clean initial and final whitespaces
			if (tasks.empty()) {
				std::cout << "Uncorrect input file" << std::endl;
				return 1;
			}
			auto s = trim(str);
			if (!s.empty())
				tasks[tasks.size() - 1]->add_action(s);
		}
	}

	if (!tasks.empty() && tasks[tasks.size() - 1]->get_actions().empty()) {
		std::cout << "Warning: no actions for target " << tasks[tasks.size() - 1]->get_target() << std::endl;
	}

	try {
		if (!fin.eof()) throw std::runtime_error("Invalid data from file");
		fin.close();
		if (maps.count(command) == 0) {
			throw my_exception("Uncorrect dependence: no target \"" + command + "\"");
		}
		//start execute dependence-tree
		dfs(command);
	} catch (std::exception& e){
		std::cout << e.what() << std::endl;
		//std::cout << "ochen zhal" << std::endl;
	}
	
	//std::system("pause");

}