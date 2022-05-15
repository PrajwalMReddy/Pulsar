#ifndef CODEPULSAR_INTERPRETER_H
#define CODEPULSAR_INTERPRETER_H

#include <iostream>

using namespace std;


class Interpreter {
    public:
        Interpreter(string sourceCode);
        void interpret();

    private:
        string sourceCode;
};


#endif
