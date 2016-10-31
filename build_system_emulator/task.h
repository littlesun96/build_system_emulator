#ifndef TASK_H
#define TASK_H

#include<string>
#include<vector>

class task {
public:
	task();
	task(std::string target) {
		this->target = target;
		this->status = -1;
	}
	void set_dependences(std::vector<std::string> dependences);
	void set_actions(std::vector<std::string> actions);
	void set_target(std::string target);
	void set_status(int status);
	void add_action(std::string action);
	std::vector<std::string> get_dependeces();
	std::vector<std::string> get_actions();
	std::string get_target();
	int get_status();

	~task();
private:
	std::string target;
	std::vector<std::string> dependences;
	std::vector<std::string> actions;
	int status;
};

#endif // !TASK_H