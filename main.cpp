#include "Processor.hpp"
#include "Utils.hpp"

const unsigned short BITS = 30;

int main(int argc, char** cargs) {
	bool isFileInput;
	char* filename;
	std::ifstream inputFile;
	if (argc == 2) {
		filename = cargs[1];
		inputFile.open(filename);
		isFileInput = inputFile.is_open();
	} else {
		isFileInput = false;
	}

	std::string line, command;
	std::vector<std::string> args;

	bool shouldPollCommand = true;

	Processor proc(BITS);

	if (!isFileInput) {
		std::cout << "Input file wasn't found. Starting in CLI mode\n\n";
	} else {
		std::cout << "Reading commands from file: " << filename << std::endl << std::endl;
	}

	std::cout << "Processor is turned on.\n";
	while (shouldPollCommand) {
		if (isFileInput && inputFile.good()) {
			std::getline(inputFile, line);
		} else {
			Utils::getUserLine(line);
		}

		Utils::parse(line, command, args);
		proc.pollCommand(command, args);
		std::vector<std::string>().swap(args);
		shouldPollCommand = (isFileInput ? inputFile.good() : true) && proc.getState();
	}
	std::cout << "Processor is turned off." << std::endl;

	if (argc == 2) {
		inputFile.close();
	}

	return 0;
}
