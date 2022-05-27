#ifndef CODEPULSAR_COMMANDS_H
#define CODEPULSAR_COMMANDS_H

#include <iostream>
#include <string>

#include "../pulsar/Pulsar.h"
#include "SetUp.h"


namespace Pulsar {
    void help();
    void error(std::string message);

    void parseCommands(std::string command);
    void parseCommands(std::string command, std::string file);

    void debug();
    void version();
    void setUp(std::string name);
}

#endif
