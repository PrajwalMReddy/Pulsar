#ifndef CODEPULSAR_TOKENTYPE_H
#define CODEPULSAR_TOKENTYPE_H


namespace Pulsar {
    enum TokenType {
        // Operators
        TK_NOT, // Unary
        TK_MINUS, TK_PLUS, TK_MULTIPLICATION, TK_DIVISION, TK_MODULUS, // Binary
        TK_NOT_EQUAL, TK_EQUAL_EQUAL, TK_GT, TK_GT_EQUAL, TK_LT, TK_LT_EQUAL, // Comparison
        TK_EQUAL, TK_PLUS_EQUAL, TK_MINUS_EQUAL, TK_MUL_EQUAL, TK_DIV_EQUAL, TK_MOD_EQUAL, // Assignment
        TK_LOGICAL_OR, TK_LOGICAL_AND, // Logical

        // Other Character Tokens
        TK_DOT, TK_COMMA, TK_SEMICOLON,
        TK_LPAR, TK_RPAR, TK_LBRACE, TK_RBRACE,
        TK_COLON, TK_ARROW, TK_DOUBLE_COLON, TK_QMARK,

        // Keywords
        TK_PACKAGE, TK_NAMESPACE, TK_IMPORT,
        TK_CLASS, TK_TRAIT, TK_ENUM,
        TK_EXTENDS, TK_IMPLEMENTS,
        TK_VAR, TK_CONST,
        TK_IF, TK_ELSE, TK_WHILE,
        TK_CONTINUE, TK_BREAK,
        TK_FUN, TK_NATIVE, TK_METHOD, TK_INIT,
        TK_STATIC, TK_OVERRIDE,
        TK_PUBLIC, TK_PRIVATE, TK_RETURN,

        // Reserved Keywords (For Possible Future Use)
        TK_MATCH, TK_LOOP,
        TK_TRY, TK_EXCEPT,
        TK_MOD, TK_USE, TK_INTERNAL,
        TK_ASYNC, TK_AWAIT,
        TK_UNSAFE,

        // Data Types and Variables
        TK_IDENTIFIER, TK_VOID,
        TK_INT_TYPE, TK_DOUBLE_TYPE, TK_BOOLEAN_TYPE, TK_CHAR_TYPE,
        TK_TRUE, TK_FALSE, TK_CHARACTER, TK_INTEGER, TK_DOUBLE,

        // Special Tokens
        TK_PRINT,
        TK_ERROR, TK_EOF,
    };
}


#endif
