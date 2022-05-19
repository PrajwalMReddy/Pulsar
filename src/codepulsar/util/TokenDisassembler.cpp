#include "TokenDisassembler.h"


void TokenDisassembler::display(vector<Token> tokens) {
    if (setUpConditions.debug) {
        cout << "-- Tokens --" << endl;
        displayTokens(tokens);
    }
}

void TokenDisassembler::displayTokens(vector<Token> tokens) {
    int line = 0;

    for (Token token: tokens) {
        string tokenName = checkToken(token.tokenType);
        if (token.line == line) {
            cout << "            ";
        } else {
            line = token.line;
            cout << endl << line << space(line);
        }

        if (isLiteralTokenType(token.tokenType)) {
            cout << tokenName << space(token) << "(" + token.literal << ")" << endl;
        } else {
            cout << tokenName << endl;
        }
    }
}

// TODO Add Reserved Keywords; Make More Elegant
string TokenDisassembler::checkToken(TokenType type) {
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
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_DOUBLE_COLON: return "TK_DOUBLE_COLON";
        case TK_QMARK: return "TK_QMARK";
        case TK_LPAR: return "TK_LPAR";
        case TK_RPAR: return "TK_RPAR";
        case TK_LBRACE: return "TK_LBRACE";
        case TK_RBRACE: return "TK_RBRACE";

        case TK_PACKAGE: return "TK_PACKAGE";
        case TK_IMPORT: return "TK_IMPORT";
        case TK_CLASS: return "TK_CLASS";
        case TK_ENUM: return "TK_ENUM";
        case TK_VAR: return "TK_VAR";
        case TK_CONST: return "TK_CONST";
        case TK_IF: return "TK_IF";
        case TK_ELSE: return "TK_ELSE";
        case TK_WHILE: return "TK_CONTINUE";
        case TK_BREAK: return "TK_BREAK";
        case TK_FUN: return "TK_FUN";
        case TK_NATIVE: return "TK_NATIVE";
        case TK_OPERATOR: return "TK_OPERATOR";
        case TK_PUBLIC: return "TK_PUBLIC";
        case TK_PRIVATE: return "TK_PRIVATE";
        case TK_STATIC: return "TK_STATIC";
        case TK_RETURN: return "TK_RETURN";

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

bool TokenDisassembler::isLiteralTokenType(TokenType type) {
    switch (type) {
        case TK_CHARACTER: return true;
        case TK_INTEGER: return true;
        case TK_DOUBLE: return true;
        case TK_IDENTIFIER: return true;
        default: return false;
    }
}

string TokenDisassembler::space(int line) {
    int length = to_string(line).length();
    return giveSpaces(length + 9);
}

string TokenDisassembler::space(Token token) {
    int length = to_string(token.tokenType).length();
    return giveSpaces(length);
}

string TokenDisassembler::giveSpaces(int length) {
    return string(" ", max(0, 20 - length + 1));
}
