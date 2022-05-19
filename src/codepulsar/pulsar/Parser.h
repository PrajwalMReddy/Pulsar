#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <iostream>
#include <vector>

#include "../lang/Token.h"
#include "../lang/CompilerError.h"
#include "../ast/Statement.h"
#include "../util/TokenDisassembler.h"

using namespace std;


class Parser {
    public:
        Parser(string sourceCode);
        Statement parse();

    private:
        // Input Data
        string sourceCode;
        vector<Token> tokens;
        CompilerError errors;

        // Processing Data
        int current;
        int depth;

        // Output Data
        Statement program;
};


#endif
