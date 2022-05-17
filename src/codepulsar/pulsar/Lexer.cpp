#include "Lexer.h"


Lexer::Lexer(string sourceCode) {
    this->sourceCode = sourceCode;

    this->start = 0;
    this->current = 0;
    this->line = 1;
}

vector<Token> Lexer::tokenize() {
    while (true) {
        Token toAdd = scanToken();
        this->tokens.push_back(toAdd);

        if (toAdd.tokenType == TK_EOF) break;
    }

    return this->tokens;
}

Token Lexer::scanToken() {
    skipWhitespace();
    this->start = this->current;

    if (isAtEnd()) return makeToken(TK_EOF);

    char now = advance();
    if (isAlpha(now)) { return identifier(); }
    if (isDigit(now)) { return number(); }
    return character(now);
}

Token Lexer::identifier() {
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }

    return makeToken(identifyIdentifier());
}

TokenType Lexer::identifyIdentifier() {
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
    if (currentLiteral() == "fun") return TK_FUN;
    if (currentLiteral() == "false") return TK_FALSE;
    if (currentLiteral() == "if") return TK_IF;
    if (currentLiteral() == "import") return TK_IMPORT;
    if (currentLiteral() == "int") return TK_INT_TYPE;
    if (currentLiteral() == "loop") return TK_LOOP;
    if (currentLiteral() == "mod") return TK_MOD;
    if (currentLiteral() == "match") return TK_MATCH;
    if (currentLiteral() == "native") return TK_NATIVE;
    if (currentLiteral() == "operator") return TK_OPERATOR;
    if (currentLiteral() == "package") return TK_PACKAGE;
    if (currentLiteral() == "print") return TK_PRINT;
    if (currentLiteral() == "private") return TK_PRIVATE;
    if (currentLiteral() == "public") return TK_PUBLIC;
    if (currentLiteral() == "return") return TK_RETURN;
    if (currentLiteral() == "static") return TK_STATIC;
    if (currentLiteral() == "true") return TK_TRUE;
    if (currentLiteral() == "try") return TK_TRY;
    if (currentLiteral() == "unsafe") return TK_UNSAFE;
    if (currentLiteral() == "var") return TK_VAR;
    if (currentLiteral() == "void") return TK_VOID;
    if (currentLiteral() == "while") return TK_WHILE;
    else return TK_IDENTIFIER;
}

Token Lexer::number() {
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
    } catch (exception) {
        errorToken("Invalid Value For Integer: " + currentLiteral());
    }

    return makeToken(TK_INTEGER);
}

Token Lexer::character(char now) {
    switch (now) {
        case '.':
            return makeToken(TK_DOT);
        case ',':
            return makeToken(TK_COMMA);
        case ':':
            if (peek() == ':') {
                advance();
                return makeToken(TK_DOUBLE_COLON);
            } else {
                makeToken(TK_COLON);
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
                return errorToken("Invalid Character: '" + to_string(now) + "'. Perhaps You Meant Logical Or: ||");
            }
        case '&':
            if (peek() == '&') {
                advance();
                return makeToken(TK_LOGICAL_AND);
            } else {
                return errorToken("Invalid Character: '" + to_string(now) + "'. Perhaps You Meant Logical And: &&");
            }

        default: return errorToken("Invalid Character: " + to_string(now));
    }
}

Token Lexer::charLiteral() {
    while (peek() != '\'' && !isAtEnd()) {
        if (peek() == '\n') this->line++;
        advance();
    }

    if (isAtEnd()) return errorToken("Char Literal Not Closed");
    advance();
    if (currentLiteral().length() != 3) return errorToken("A Char May Only Contain 1 Character");

    return makeToken(TK_CHARACTER);
}

Token Lexer::makeToken(TokenType tokenType) {
    return Token(tokenType, currentLiteral(), this->line);
}

Token Lexer::errorToken(string message) {
    Token errorToken = Token(TK_ERROR, message, this->line);
    this->errors->addError("Tokenizing Error", message, this->line);
    return errorToken;
}

void Lexer::skipWhitespace() {
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

string Lexer::currentLiteral() {
    return this->sourceCode.substr(this->start, this->current);
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return this->sourceCode[this->current];
}

char Lexer::peek(int skip) {
    if (isAtEnd()) return '\0';
    return this->sourceCode[this->current + skip];
}

char Lexer::advance() {
    this->current++;
    return this->sourceCode[this->current - 1];
}

bool Lexer::isAtEnd() {
    return this->current >= this->sourceCode.length();
}

CompilerError* Lexer::getErrors() {
    return this->errors;
}