#ifndef CODEPULSAR_PARSER_H
#define CODEPULSAR_PARSER_H

#include <iostream>

using namespace std;


class Parser {
    public:
        Parser(string sourceCode);
        void parse();

    private:
        string sourceCode;
};


#endif
