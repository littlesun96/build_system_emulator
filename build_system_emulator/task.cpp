#include "task.h"



task::task()
{
}


void task::set_dependences(std::vector<std::string> dependences) {
	this->dependences = dependences;
}

void task::set_actions(std::vector<std::string> actions) {
	this->actions = actions;
}

void task::set_target(std::string target) {
	this->target = target;
}

void task::set_status(int status) {
	this->status = status;
}

void task::add_action(std::string action) {
	actions.push_back(action);
}

std::vector<std::string> task::get_dependeces() {
	return this->dependences;
}

std::vector<std::string> task::get_actions() {
	return this->actions;
}

std::string task::get_target() {
	return this->target;
}

int task::get_status() {
	return this->status;
}

task::~task()
{
}
