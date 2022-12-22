#include "Lexer.h"


Pulsar::Lexer::Lexer(std::string sourceCode) {
    this->sourceCode = sourceCode;

    this->start = 0;
    this->current = 0;
    this->line = 1;

    this->errors = new CompilerError();
}

std::vector<Pulsar::Token> Pulsar::Lexer::tokenize() {
    if (this->sourceCode.empty()) return this->tokens;

    while (true) {
        Token toAdd = scanToken();
        this->tokens.push_back(toAdd);

        if (toAdd.tokenType == TK_EOF) break;
    }

    return this->tokens;
}

Pulsar::Token Pulsar::Lexer::scanToken() {
    skipWhitespace();
    this->start = this->current;

    if (isAtEnd()) return makeToken(TK_EOF);

    char now = advance();
    if (isAlpha(now)) { return scanIdentifier(); }
    if (isDigit(now)) { return scanNumber(); }
    return scanCharacter(now);
}

Pulsar::Token Pulsar::Lexer::scanIdentifier() {
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }

    return makeToken(identifyIdentifier());
}

Pulsar::TokenType Pulsar::Lexer::identifyIdentifier() {
    if (currentLiteral() == "async") return TK_ASYNC;
    if (currentLiteral() == "await") return TK_AWAIT;
    if (currentLiteral() == "break") return TK_BREAK;
    if (currentLiteral() == "boolean") return TK_BOOLEAN_TYPE;
    if (currentLiteral() == "char") return TK_CHAR_TYPE;
    if (currentLiteral() == "class") return TK_CLASS;
    if (currentLiteral() == "const") return TK_CONST;
    if (currentLiteral() == "continue") return TK_CONTINUE;
    if (currentLiteral() == "double") return TK_DOUBLE_TYPE;
    if (currentLiteral() == "else") return TK_ELSE;
    if (currentLiteral() == "enum") return TK_ENUM;
    if (currentLiteral() == "except") return TK_EXCEPT;
    if (currentLiteral() == "extends") return TK_EXTENDS;
    if (currentLiteral() == "fun") return TK_FUN;
    if (currentLiteral() == "false") return TK_FALSE;
    if (currentLiteral() == "if") return TK_IF;
    if (currentLiteral() == "implements") return TK_IMPLEMENTS;
    if (currentLiteral() == "import") return TK_IMPORT;
    if (currentLiteral() == "init") return TK_INIT;
    if (currentLiteral() == "int") return TK_INT_TYPE;
    if (currentLiteral() == "internal") return TK_INTERNAL;
    if (currentLiteral() == "loop") return TK_LOOP;
    if (currentLiteral() == "match") return TK_MATCH;
    if (currentLiteral() == "method") return TK_METHOD;
    if (currentLiteral() == "mod") return TK_MOD;
    if (currentLiteral() == "namespace") return TK_NAMESPACE;
    if (currentLiteral() == "native") return TK_NATIVE;
    if (currentLiteral() == "override") return TK_OVERRIDE;
    if (currentLiteral() == "package") return TK_PACKAGE;
    if (currentLiteral() == "print") return TK_PRINT;
    if (currentLiteral() == "private") return TK_PRIVATE;
    if (currentLiteral() == "public") return TK_PUBLIC;
    if (currentLiteral() == "return") return TK_RETURN;
    if (currentLiteral() == "static") return TK_STATIC;
    if (currentLiteral() == "trait") return TK_TRAIT;
    if (currentLiteral() == "true") return TK_TRUE;
    if (currentLiteral() == "try") return TK_TRY;
    if (currentLiteral() == "unsafe") return TK_UNSAFE;
    if (currentLiteral() == "use") return TK_USE;
    if (currentLiteral() == "var") return TK_VAR;
    if (currentLiteral() == "void") return TK_VOID;
    if (currentLiteral() == "while") return TK_WHILE;
    else return TK_IDENTIFIER;
}

Pulsar::Token Pulsar::Lexer::scanNumber() {
    int dotCount = 0;

    while (isDigit(peek()) || peek() == '.') {
        if (peek() == '.') dotCount++;
        advance();
    }

    if (dotCount == 1 && currentLiteral().back() != '.') {
        return makeToken(TK_DOUBLE);
    } else if (dotCount > 1) {
        return errorToken("Invalid Number Literal: " + currentLiteral());
    } else if (currentLiteral().back() == '.') {
        return errorToken("Invalid Number Literal: " + currentLiteral());
    }

    try {
        stoi(currentLiteral());
    } catch (std::exception) {
        errorToken("Invalid Value For Integer: " + currentLiteral());
    }

    return makeToken(TK_INTEGER);
}

Pulsar::Token Pulsar::Lexer::scanCharacter(char character) {
    switch (character) {
        case '.':
            return makeToken(TK_DOT);
        case ',':
            return makeToken(TK_COMMA);
        case ':':
            if (peek() == ':') {
                advance();
                return makeToken(TK_DOUBLE_COLON);
            } else {
                return makeToken(TK_COLON);
            }
        case ';':
            return makeToken(TK_SEMICOLON);
        case '?':
            return makeToken(TK_QMARK);
        case '(':
            return makeToken(TK_LPAR);
        case ')':
            return makeToken(TK_RPAR);
        case '{':
            return makeToken(TK_LBRACE);
        case '}':
            return makeToken(TK_RBRACE);
        case '\'':
            return charLiteral();

        case '!':
            if (peek() == '=') {
                advance();
                return makeToken(TK_NOT_EQUAL);
            } else {
                return makeToken(TK_NOT);
            }
        case '+':
            if (peek() == '=') {
                advance();
                return makeToken(TK_PLUS_EQUAL);
            } else {
                return makeToken(TK_PLUS);
            }
        case '-':
            if (peek() == '=') {
                advance();
                return makeToken(TK_MINUS_EQUAL);
            } else if (peek() == '>') {
                advance();
                return makeToken(TK_ARROW);
            } else {
                return makeToken(TK_MINUS);
            }
        case '*':
            if (peek() == '=') {
                advance();
                return makeToken(TK_MUL_EQUAL);
            } else {
                return makeToken(TK_MULTIPLICATION);
            }
        case '/':
            if (peek() == '=') {
                advance();
                return makeToken(TK_DIV_EQUAL);
            } else {
                return makeToken(TK_DIVISION);
            }
        case '%':
            if (peek() == '=') {
                advance();
                return makeToken(TK_MOD_EQUAL);
            } else {
                return makeToken(TK_MODULUS);
            }

        case '=':
            if (peek() == '=') {
                advance();
                return makeToken(TK_EQUAL_EQUAL);
            } else {
                return makeToken(TK_EQUAL);
            }
        case '>':
            if (peek() == '=') {
                advance();
                return makeToken(TK_GT_EQUAL);
            } else {
                return makeToken(TK_GT);
            }
        case '<':
            if (peek() == '=') {
                advance();
                return makeToken(TK_LT_EQUAL);
            } else {
                return makeToken(TK_LT);
            }
        case '|':
            if (peek() == '|') {
                advance();
                return makeToken(TK_LOGICAL_OR);
            } else {
                return errorToken(std::string("Invalid Character: '") + character + std::string("'. Perhaps You Meant Logical Or: ||"));
            }
        case '&':
            if (peek() == '&') {
                advance();
                return makeToken(TK_LOGICAL_AND);
            } else {
                return errorToken(std::string("Invalid Character: '") + character + std::string("'. Perhaps You Meant Logical And: &&"));
            }

        default: return errorToken(std::string("Invalid Character: ") + character);
    }
}

Pulsar::Token Pulsar::Lexer::charLiteral() {
    while (peek() != '\'' && !isAtEnd()) {
        if (peek() == '\n') this->line++;
        advance();
    }

    if (isAtEnd()) return errorToken("The Char Literal Has Not Been Closed");
    advance();
    if (currentLiteral().length() != 3) return errorToken("A Char May Only Contain 1 Character");

    return makeToken(TK_CHARACTER);
}

Pulsar::Token Pulsar::Lexer::makeToken(Pulsar::TokenType tokenType) {
    return Pulsar::Token(tokenType, currentLiteral(), this->line);
}

Pulsar::Token Pulsar::Lexer::errorToken(std::string message) {
    Pulsar::Token errorToken = Token(TK_ERROR, message, this->line);
    this->errors->addError("Tokenizing Error", message, this->line);
    return errorToken;
}

void Pulsar::Lexer::skipWhitespace() {
    while (true) {
        char next = peek();

        switch (next) {
            case ' ': case '\r': case '\t':
                advance();
                break;

            case '\n':
                this->line++;
                advance();
                break;

            case '/':
                if (peek(1) == '/') { while (peek() != '\n' && !isAtEnd()) { advance(); } }
                else return;
                break;

            default:
                return;
        }
    }
}

std::string Pulsar::Lexer::currentLiteral() {
    return this->sourceCode.substr(this->start, this->current - this->start);
}

bool Pulsar::Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Pulsar::Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char Pulsar::Lexer::peek() {
    if (isAtEnd()) return '\0';
    return this->sourceCode[this->current];
}

char Pulsar::Lexer::peek(int skip) {
    if (isAtEnd()) return '\0';
    return this->sourceCode[this->current + skip];
}

char Pulsar::Lexer::advance() {
    this->current++;
    return this->sourceCode[this->current - 1];
}

bool Pulsar::Lexer::isAtEnd() {
    return this->current >= this->sourceCode.length();
}

Pulsar::CompilerError* Pulsar::Lexer::getErrors() {
    return this->errors;
}