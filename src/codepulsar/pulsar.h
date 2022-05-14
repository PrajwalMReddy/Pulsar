#ifndef CODEPULSAR_PULSAR_H
#define CODEPULSAR_PULSAR_H

#include "commands.h"

using namespace std;


struct SetUp {
    string fileIn;
    bool debug;
    string version;
};

extern SetUp setUpStruct;

void repl();
void interpretFile(string file);
void compileFile(string file);

#endif
