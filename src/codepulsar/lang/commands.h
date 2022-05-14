#ifndef CODEPULSAR_COMMANDS_H
#define CODEPULSAR_COMMANDS_H

#include <iostream>

#include "../pulsar/pulsar.h"

using namespace std;

void help();
void error(string message);

void parseCommands(string command);
void parseCommands(string command, string file);

void debug();
void version();
void setUp(string name);

#endif
