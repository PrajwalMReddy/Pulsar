#ifndef CODEPULSAR_PULSAR_H
#define CODEPULSAR_PULSAR_H

#include <string>
#include <fstream>

#include "Compiler.h"
#include "Interpreter.h"
#include "../lang/SetUp.h"
#include "../lang/Commands.h"


namespace Pulsar {
    void repl();
    void interpretFile(std::string file);
    void compileFile(std::string file);

    std::string openFile(std::string file);
}


#endif
