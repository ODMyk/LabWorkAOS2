#include "Processor.hpp"

Processor::Processor(unsigned bits): BITS(bits), isOn(true), stateR(0), commandCountR(0), tactCountR(0) {}

void Processor::pollCommand(std::string& command, std::vector<std::string> &args) {
	if (command.empty()) {
		isOn = false;
		return;
	}

	if (!command.compare("mov")) { // std::string.compare(another_string) returns 0, if strings are equlal. !0 == 1.
		if (args.size() != 1) {
			std::cout << "Error! Wrong arguments count given to mov." << std::endl;
			return;
		}

		++commandCountR;
		tactCountR = 1;
		printInfo(command, args);
		addOnStack(std::stoll(args[0]));
	} else if (!command.compare("rpush")) {
		if (args.size() != 1) {
			std::cout << "Error! Wrong arguments count given to rpush." << std::endl;
			return;
		}
		
		unsigned long c = std::stoul(args[0]);

		if (stack.size() < c) {
			std::cout << "Error! Not enough elements on stack to apply the rpush." << std::endl;
			return;
		}

		if (c < 2) {
			std::cout << "Error! Wrong count for rpush: " << c << ". Min value is 2" << std::endl;
			return;
		}

		++commandCountR;
		tactCountR = 1;
		printInfo(command, args);
		rpush(c);
	} else if (!command.compare("lpush")) {
		if (args.size() != 1) {
			std::cout << "Error! Wrong arguments count given to lpush." << std::endl;
			return;
		}

		unsigned long c = std::stoul(args.at(0));

		if (stack.size() < c) {
			std::cout << "Error! Not enough elements on stack to apply the lpush." << std::endl;
			return;
		}


		if (c < 2) {
			std::cout << "Error! Wrong count for lpush: " << c << ". Min value is 2" << std::endl;
			return;
		}
		
		++commandCountR;
		tactCountR = 1;
		printInfo(command, args);
		lpush(c);
	} else {
		std::cout << "Error! Unknown command: " << command << std::endl;
		return;
	}

	while (getchar() != 10) {}
	tactCountR = 2;
	stateR = -2 * stack[stack.size() - 1][0] + 1;
	printInfo(command, args);
}

bool* Processor::turnTo2s(long long int n) const {
	bool* arr = new bool[BITS];
	bool negative = n < 0;

	if (negative) {
		n = -n;
	}

	for (int i = 0; i < BITS; ++i) {
		arr[BITS - 1 - i] = ((n % 2) + negative) % 2;
		n /= 2;
	}

	if (negative) {
		int i = BITS;
		do {
			--i;
			arr[i] = !arr[i];
		} while (!arr[i] && i > 0);
	}

	return arr;
}

bool Processor::addOnStack(long long n) {
	try {
		stack.push_back(turnTo2s(n));
	} catch (const std::length_error& e) {
		return false;
	}
	return true;
}

bool Processor::getState() const {
	return isOn;
}

void Processor::rpush(unsigned groupSize) {
	for (int i = 1; i <= groupSize; ++i) {
		bool* el = stack[stack.size() - i];
		bool last = el[BITS - 1];
		for (int j = BITS - 1; j > 0; --j) {
			el[j] = el[j - 1];
		}
		el[0] = last;
	}
}

void Processor::lpush(unsigned groupSize) {
	for (int i = 1; i <= groupSize; ++i) {
		bool* el = stack[stack.size() - i];
		bool first = el[0];
		for (int i = 0; i < BITS - 1; ++i) {
			el[i] = el[i + 1];
		}
		el[BITS - 1] = first;
	}
}

void Processor::printInfo(std::string& command, std::vector<std::string> &args) const {
	std::cout << std::endl << "Command: " << command;
	for (unsigned int i = 0; i < args.size(); ++i) {
		std::cout << " | " << args[i];
	}
	std::cout << std::endl;
	for (int i = stack.size() - 1; i >= 0; --i) {
		std::cout.width(7);
		std::cout << i << ": ";
		for (int j = 0; j < BITS; ++j) {
			std::cout << stack[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "     PS: " << stateR << std::endl;
	std::cout << "     PC: " << commandCountR << std::endl;
	std::cout << "     TC: " << tactCountR << std::endl;
}

Processor::~Processor() {
	for (bool* p: stack) {
		delete p;
	}
	std::vector<bool*>().swap(stack);
}
