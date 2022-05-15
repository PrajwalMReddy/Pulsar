#ifndef CODEPULSAR_PULSAR_H
#define CODEPULSAR_PULSAR_H

#include <fstream>

#include "../lang/Commands.h"

using namespace std;


struct SetUp {
    string fileIn;
    bool debug;
    string version;
};

extern SetUp setUpConditions;

void repl();
void interpretFile(string file);
void compileFile(string file);

string openFile(string file);

#endif
