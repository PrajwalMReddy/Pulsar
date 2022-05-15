#ifndef CODEPULSAR_LEXER_H
#define CODEPULSAR_LEXER_H

#include <iostream>

using namespace std;


class Lexer {
    public:
        Lexer(string sourceCode);
        void tokenize();

    private:
        string sourceCode;
};


#endif
