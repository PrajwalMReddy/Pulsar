#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <string>

#include "Lexer.h"
#include "../util/TokenDisassembler.h"


namespace Pulsar {
    class Parser {
        public:
            Parser(std::string sourceCode);
            void parse();

        private:
            // Input Data
            std::string sourceCode;
            std::vector<Token> tokens;

            // Output Data
            Pulsar::CompilerError* errors;
    };
}


#endif
