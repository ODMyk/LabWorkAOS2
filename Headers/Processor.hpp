#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <cstdio>
#include <fstream>

#include "Utils.hpp"

class Processor {
public:
	Processor(unsigned bits);
	void pollCommand(std::string& command, std::vector<std::string> &args);
	bool getState() const;
	~Processor();

private:
	const unsigned BITS;
	std::vector<bool*> stack;
	unsigned commandCountR;
	unsigned tactCountR;
	short stateR;
	bool isOn;

private:
	bool* turnTo2s(long long int n) const;
	bool addOnStack(long long n);
	void lpush(unsigned groupSize);
	void rpush(unsigned groupSize);
	void printInfo(std::string& command, std::vector<std::string> &args) const;
};

#endif
