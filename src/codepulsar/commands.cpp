#include "commands.h"

void help() {
    cout << "Usage: pulsar [command] [file]" << endl;
    cout << "Commands:" << endl;
    cout << "    -h     : Shows This Help Menu" << endl;
    cout << "    -v     : Displays The Current Version Number" << endl;
    cout << "    -i     : Interprets The Given File" << endl;
    cout << "    -c     : Compiles The Given File" << endl;
    cout << "    -d     : Displays Debug Information\n"
         << "             And Interprets The File\n";

    cout << endl;
}

void error(string message) {
    help();
    cerr << "Set Up Error | " << message << endl;
    exit(1);
}

void parseCommands(string command) {
    if (command == "-h") help();
    else if (command == "-v") version();
    else error("Invalid One Argument Command: " + command);
}

void parseCommands(string command, string file) {
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

void debug() {
    setUpStruct.debug = true;
}

void version() {
    cout << "Version: " << setUpStruct.version << endl;
}

void setUp(string name) {
    setUpStruct.fileIn = name.substr(0, name.find_last_of('.'));
}