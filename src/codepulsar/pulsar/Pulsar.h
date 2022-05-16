#ifndef CODEPULSAR_PULSAR_H
#define CODEPULSAR_PULSAR_H

#include <iostream>
#include <fstream>

#include "../lang/Commands.h"
#include "../lang/SetUp.h"

using namespace std;


void repl();
void interpretFile(string file);
void compileFile(string file);

string openFile(string file);

#endif
