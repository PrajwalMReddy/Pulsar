#include "TokenDisassembler.h"


void Pulsar::TokenDisassembler::display(std::vector<Pulsar::Token> tokens) {
    if (conditions.debug) {
        std::cout << "-- Tokens --" << std::endl;
        displayTokens(tokens);
    }
}

void Pulsar::TokenDisassembler::displayTokens(std::vector<Pulsar::Token> tokens) {
    if (tokens.empty()) {
        std::cout << "\nNo Tokens Have Been Generated" << std::endl;
        return;
    }

    int line = 0;

    for (Pulsar::Token token: tokens) {
        std::string tokenName = tokenToString(token.tokenType);

        if (token.line == line) {
            std::cout << "            ";
        } else {
            line = token.line;
            std::cout << std::endl << line << space(line);
        }

        if (isLiteralTokenType(token.tokenType)) {
            std::cout << tokenName << space(token) << "(" + token.literal << ")" << std::endl;
        } else {
            std::cout << tokenName << std::endl;
        }
    }
}

std::string Pulsar::TokenDisassembler::tokenToString(Pulsar::TokenType type) {
    switch (type) {
        case TK_NOT: return "TK_NOT";
        case TK_MINUS: return "TK_MINUS";
        case TK_PLUS: return "TK_PLUS";
        case TK_MULTIPLICATION: return "TK_MULTIPLICATION";
        case TK_DIVISION: return "TK_DIVISION";
        case TK_MODULUS: return "TK_MODULUS";
        case TK_NOT_EQUAL: return "TK_NOT_EQUAL";
        case TK_EQUAL_EQUAL: return "TK_EQUAL_EQUAL";
        case TK_GT: return "TK_GT";
        case TK_GT_EQUAL: return "TK_GT_EQUAL";
        case TK_LT: return "TK_LT";
        case TK_LT_EQUAL: return "TK_LT_EQUAL";
        case TK_EQUAL: return "TK_EQUAL";
        case TK_PLUS_EQUAL: return "TK_PLUS_EQUAL";
        case TK_MINUS_EQUAL: return "TK_MINUS_EQUAL";
        case TK_MUL_EQUAL: return "TK_MUL_EQUAL";
        case TK_DIV_EQUAL: return "TK_DIV_EQUAL";
        case TK_MOD_EQUAL: return "TK_MOD_EQUAL";
        case TK_LOGICAL_OR: return "TK_LOGICAL_OR";
        case TK_LOGICAL_AND: return "TK_LOGICAL_AND";

        case TK_DOT: return "TK_DOT";
        case TK_COMMA: return "TK_COMMA";
        case TK_COLON: return "TK_COLON";
        case TK_ARROW: return "TK_ARROW";
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_DOUBLE_COLON: return "TK_DOUBLE_COLON";
        case TK_QMARK: return "TK_QMARK";
        case TK_LPAR: return "TK_LPAR";
        case TK_RPAR: return "TK_RPAR";
        case TK_LBRACE: return "TK_LBRACE";
        case TK_RBRACE: return "TK_RBRACE";

        case TK_PACKAGE: return "TK_PACKAGE";
        case TK_NAMESPACE: return "TK_NAMESPACE";
        case TK_IMPORT: return "TK_IMPORT";
        case TK_CLASS: return "TK_CLASS";
        case TK_TRAIT: return "TK_TRAIT";
        case TK_ENUM: return "TK_ENUM";
        case TK_EXTENDS: return "TK_EXTENDS";
        case TK_IMPLEMENTS: return "TK_IMPLEMENTS";
        case TK_VAR: return "TK_VAR";
        case TK_CONST: return "TK_CONST";
        case TK_IF: return "TK_IF";
        case TK_ELSE: return "TK_ELSE";
        case TK_WHILE: return "TK_WHILE";
        case TK_CONTINUE: return "TK_CONTINUE";
        case TK_BREAK: return "TK_BREAK";
        case TK_FUN: return "TK_FUN";
        case TK_NATIVE: return "TK_NATIVE";
        case TK_METHOD: return "TK_METHOD";
        case TK_INIT: return "TK_INIT";
        case TK_STATIC: return "TK_STATIC";
        case TK_OVERRIDE: return "TK_OVERRIDE";
        case TK_PUBLIC: return "TK_PUBLIC";
        case TK_PRIVATE: return "TK_PRIVATE";
        case TK_RETURN: return "TK_RETURN";

        case TK_MATCH: return "TK_MATCH";
        case TK_LOOP: return "TK_LOOP";
        case TK_TRY: return "TK_TRY";
        case TK_EXCEPT: return "TK_EXCEPT";
        case TK_MOD: return "TK_MOD";
        case TK_USE: return "TK_USE";
        case TK_INTERNAL: return "TK_INTERNAL";
        case TK_ASYNC: return "TK_ASYNC";
        case TK_AWAIT: return "TK_AWAIT";
        case TK_UNSAFE: return "TK_UNSAFE";

        case TK_IDENTIFIER: return "TK_IDENTIFIER";
        case TK_VOID: return "TK_VOID";
        case TK_INT_TYPE: return "TK_INT_TYPE";
        case TK_DOUBLE_TYPE: return "TK_DOUBLE_TYPE";
        case TK_BOOLEAN_TYPE: return "TK_BOOLEAN_TYPE";
        case TK_CHAR_TYPE: return "TK_CHAR_TYPE";
        case TK_TRUE: return "TK_TRUE";
        case TK_FALSE: return "TK_FALSE";
        case TK_CHARACTER: return "TK_CHARACTER";
        case TK_INTEGER: return "TK_INTEGER";
        case TK_DOUBLE: return "TK_DOUBLE";

        case TK_PRINT: return "TK_PRINT";
        case TK_ERROR: return "TK_ERROR";
        case TK_EOF: return "TK_EOF";
        default: return "Unsupported Token Type";
    }
}

bool Pulsar::TokenDisassembler::isLiteralTokenType(TokenType type) {
    switch (type) {
        case TK_CHARACTER: return true;
        case TK_INTEGER: return true;
        case TK_DOUBLE: return true;
        case TK_IDENTIFIER: return true;
        default: return false;
    }
}

std::string Pulsar::TokenDisassembler::space(int line) {
    int length = std::to_string(line).length();
    return giveSpaces(length + 9);
}

std::string Pulsar::TokenDisassembler::space(Token token) {
    int length = tokenToString(token.tokenType).length();
    return giveSpaces(length);
}

std::string Pulsar::TokenDisassembler::giveSpaces(int length) {
    std::string str;

    for (int i = 0; i < std::max(0, 20 - length + 1); i++) {
        str += " ";
    }

    return str;
}
