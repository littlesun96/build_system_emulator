#ifndef my_exception_h
#define my_exception_h

#include <iostream>
#include <exception>
#include <cstring>

class my_exception : public std::exception {
private:
	std::string message_;
public:
	explicit my_exception(const std::string& message);
	virtual const char* what() const throw() {
		return message_.c_str();
	}
};


my_exception::my_exception(const std::string& message) : message_(message) {

}

#endif