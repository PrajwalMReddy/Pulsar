#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <iostream>
#include <vector>

#include "../lang/Token.h"
#include "../lang/CompilerError.h"
#include "../util/TokenDisassembler.h"

using namespace std;


class Parser {
    public:
        Parser(string sourceCode);
        int parse();

    private:
        // Input Data
        string sourceCode;
        vector<Token> tokens;
        CompilerError errors;

        // Processing Data
        int current;
        int depth;

        // Output Data
        int program;
};


#endif
