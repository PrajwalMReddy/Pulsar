#ifndef CODEPULSAR_COMPILER_H
#define CODEPULSAR_COMPILER_H

#include <iostream>

using namespace std;


class Compiler {
    public:
        Compiler(string sourceCode);
        void init();

    private:
        string sourceCode;
};


#endif
