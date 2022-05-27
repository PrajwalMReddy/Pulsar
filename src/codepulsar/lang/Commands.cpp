#include "Commands.h"


void Pulsar::help() {
    std::cout << "Usage: pulsar [command] [file]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "    -h     : Shows This Help Menu" << std::endl;
    std::cout << "    -v     : Displays The Current Version Number" << std::endl;
    std::cout << "    -i     : Interprets The Given File" << std::endl;
    std::cout << "    -c     : Compiles The Given File" << std::endl;
    std::cout << "    -d     : Displays Debug Information\n"
              << "             And Interprets The File\n" << std::endl;
}

void Pulsar::error(std::string message) {
    help();
    std::cout << "Set Up Error | " << message << std::endl;
    exit(1);
}

void Pulsar::parseCommands(std::string command) {
    if (command == "-h") help();
    else if (command == "-v") version();
    else error("Invalid One Argument Command: " + command);
}

void Pulsar::parseCommands(std::string command, std::string file) {
    setUp(file);

    if (command == "-h") help();
    else if (command == "-i") interpretFile(file);
    else if (command == "-c") compileFile(file);

    else if (command == "-d") {
        debug();
        interpretFile(file);
    }

    else error("Invalid Two Argument Command: " + command);
}

void Pulsar::debug() {
    conditions.debug = true;
}

void Pulsar::version() {
    std::cout << "Version: " << conditions.version << std::endl;
}

void Pulsar::setUp(std::string name) {
    conditions.fileIn = name.substr(0, name.find_last_of('.'));
}
